package org.dolphinemu.dolphinemu.utils;

import android.annotation.TargetApi;
import android.app.job.JobInfo;
import android.app.job.JobScheduler;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Context;
import android.content.res.Resources;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.VectorDrawable;
import android.media.tv.TvContract;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.PersistableBundle;
import android.support.annotation.AnyRes;
import android.support.annotation.NonNull;
import android.support.media.tv.Channel;
import android.support.media.tv.TvContractCompat;
import android.util.Log;

import org.dolphinemu.dolphinemu.R;
import org.dolphinemu.dolphinemu.model.GameFile;
import org.dolphinemu.dolphinemu.model.HomeScreenChannel;
import org.dolphinemu.dolphinemu.services.SyncChannelJobService;
import org.dolphinemu.dolphinemu.services.SyncProgramsJobService;
import org.dolphinemu.dolphinemu.ui.platform.Platform;

import java.io.File;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.List;

import static android.content.Intent.FLAG_GRANT_READ_URI_PERMISSION;
import static android.support.v4.content.FileProvider.getUriForFile;

/**
 * Assists in TV related services, e.g., home screen channels
 */
public class TvUtil
{
	private static final String TAG = "TvUtil";
	private static final long CHANNEL_JOB_ID_OFFSET = 1000;

	private static final String[] CHANNELS_PROJECTION = {
		TvContractCompat.Channels._ID,
		TvContract.Channels.COLUMN_DISPLAY_NAME,
		TvContractCompat.Channels.COLUMN_BROWSABLE
	};
	private static final String LEANBACK_PACKAGE = "com.google.android.tvlauncher";

	public static int getNumberOfChannels(Context context)
	{
		Cursor cursor =
			context.getContentResolver()
				.query(
					TvContractCompat.Channels.CONTENT_URI,
					CHANNELS_PROJECTION,
					null,
					null,
					null);
		return cursor != null ? cursor.getCount() : 0;
	}

	public static List<Channel> getAllChannels(Context context)
	{
		List<Channel> channels = new ArrayList<>();
		Cursor cursor =
			context.getContentResolver()
				.query(
					TvContractCompat.Channels.CONTENT_URI,
					CHANNELS_PROJECTION,
					null,
					null,
					null);
		if (cursor != null && cursor.moveToFirst())
		{
			do
			{
				channels.add(Channel.fromCursor(cursor));
			} while (cursor.moveToNext());
		}
		return channels;
	}

	public static Channel getChannelById(Context context, long channelId)
	{
		for (Channel channel : getAllChannels(context))
		{
			if (channel.getId() == channelId)
			{
				return channel;
			}
		}
		return null;
	}

	/**
	 * Updates all Leanback homescreen channels
	 */
	public static void updateAllChannels(Context context)
	{
		if (Build.VERSION.SDK_INT < 26)
			return;
		for (Channel channel : getAllChannels(context))
		{
			context.getContentResolver()
				.update(
					TvContractCompat.buildChannelUri(channel.getId()),
					channel.toContentValues(),
					null,
					null);
		}
	}

	public static Uri getUriToResource(Context context, @AnyRes int resId)
		throws Resources.NotFoundException
	{
		Resources res = context.getResources();
		Uri resUri = Uri.parse(ContentResolver.SCHEME_ANDROID_RESOURCE +
			"://" + res.getResourcePackageName(resId)
			+ '/' + res.getResourceTypeName(resId)
			+ '/' + res.getResourceEntryName(resId));
		return resUri;
	}

	/**
	 * Converts a resource into a {@link Bitmap}. If the resource is a vector drawable, it will be
	 * drawn into a new Bitmap. Otherwise the {@link BitmapFactory} will decode the resource.
	 */
	@NonNull
	public static Bitmap convertToBitmap(Context context, int resourceId)
	{
		Drawable drawable = context.getDrawable(resourceId);
		if (drawable instanceof VectorDrawable)
		{
			Bitmap bitmap =
				Bitmap.createBitmap(
					drawable.getIntrinsicWidth(),
					drawable.getIntrinsicHeight(),
					Bitmap.Config.ARGB_8888);
			Canvas canvas = new Canvas(bitmap);
			drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
			drawable.draw(canvas);
			return bitmap;
		}
		return BitmapFactory.decodeResource(context.getResources(), resourceId);
	}

	/**
	 * Leanback lanucher requires a uri for poster art, so we take the banner vector,
	 * make a bitmap, save that bitmap, then return the file provider uri.
	 */
	public static Uri buildBanner(GameFile game, Context context)
	{
		Uri contentUri = null;

		try
		{
			//Substring needed to strip "file:" from the path beginning
			File screenshotFile = new File(game.getScreenshotPath().substring(5));
			if (screenshotFile.exists())
			{
				contentUri = getUriForFile(context, getFilePrivider(context), screenshotFile);
			}
			else
			{
				File file = new File(buildBannerFilename(game.getGameId()));
				if (!file.exists())
				{
					int[] vector = game.getBanner();
					int width = game.getBannerWidth();
					int height = game.getBannerHeight();

					if (vector.length > 0 || width > 0 || height > 0)
					{
						Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
						bitmap.setPixels(vector, 0, width, 0, 0, width, height);
						FileOutputStream out = new FileOutputStream(file);
						bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
						out.close();
					}
					else
						return null;
				}
				contentUri = getUriForFile(context, getFilePrivider(context), file);
			}
			context.grantUriPermission(LEANBACK_PACKAGE, contentUri,
					FLAG_GRANT_READ_URI_PERMISSION);
		}
		catch (Exception e)
		{
			Log.e(TAG, "Failed to create banner");
			Log.e(TAG, e.getMessage());
		}

		return contentUri;
	}

	private static String buildBannerFilename(String gameId)
	{
		return Environment.getExternalStorageDirectory().getPath() +
			"/dolphin-emu/Cache/" + gameId + "_banner.png";
	}

	/**
	 * Needed since debug builds append '.debug' to the end of the package
	 */
	private static String getFilePrivider(Context context)
	{
		return context.getPackageName() + ".filesprovider";
	}

	/**
	 * Schedules syncing channels via a {@link JobScheduler}.
	 *
	 * @param context for accessing the {@link JobScheduler}.
	 */
	public static void scheduleSyncingChannel(Context context)
	{
		ComponentName componentName = new ComponentName(context, SyncChannelJobService.class);
		JobInfo.Builder builder = new JobInfo.Builder(1, componentName);
		builder.setRequiredNetworkType(JobInfo.NETWORK_TYPE_ANY);

		JobScheduler scheduler =
			(JobScheduler) context.getSystemService(Context.JOB_SCHEDULER_SERVICE);

		Log.d(TAG, "Scheduled channel creation.");
		scheduler.schedule(builder.build());
	}

	/**
	 * Schedulers syncing programs for a channel. The scheduler will listen to a {@link Uri} for a
	 * particular channel.
	 *
	 * @param context   for accessing the {@link JobScheduler}.
	 * @param channelId for the channel to listen for changes.
	 */
	@TargetApi(Build.VERSION_CODES.O)
	public static void scheduleSyncingProgramsForChannel(Context context, long channelId)
	{
		Log.d(TAG, "ProgramsRefresh job");
		ComponentName componentName = new ComponentName(context, SyncProgramsJobService.class);
		JobInfo.Builder builder =
			new JobInfo.Builder(getJobIdForChannelId(channelId), componentName);
		JobInfo.TriggerContentUri triggerContentUri =
			new JobInfo.TriggerContentUri(
				TvContractCompat.buildChannelUri(channelId),
				JobInfo.TriggerContentUri.FLAG_NOTIFY_FOR_DESCENDANTS);
		builder.addTriggerContentUri(triggerContentUri);
		builder.setTriggerContentMaxDelay(0L);
		builder.setTriggerContentUpdateDelay(0L);

		PersistableBundle bundle = new PersistableBundle();
		bundle.putLong(TvContractCompat.EXTRA_CHANNEL_ID, channelId);
		builder.setExtras(bundle);

		JobScheduler scheduler =
			(JobScheduler) context.getSystemService(Context.JOB_SCHEDULER_SERVICE);
		scheduler.cancel(getJobIdForChannelId(channelId));
		scheduler.schedule(builder.build());
	}

	private static int getJobIdForChannelId(long channelId)
	{
		return (int) (CHANNEL_JOB_ID_OFFSET + channelId);
	}

	/**
	 * Generates all subscriptions for homescreen channels.
	 */
	public static List<HomeScreenChannel> createUniversalSubscriptions()
	{
		//Leaving the subs local variable in case more channels are created other than platforms.
		List<HomeScreenChannel> subs = new ArrayList<>(createPlatformSubscriptions());
		return subs;
	}

	private static List<HomeScreenChannel> createPlatformSubscriptions()
	{
		List<HomeScreenChannel> subs = new ArrayList<>();
		for (Platform platform : Platform.values())
		{
			subs.add(new HomeScreenChannel(
				platform.getHeaderName(),
				platform.getHeaderName(),
				AppLinkHelper.buildBrowseUri(platform.getHeaderName()).toString()));
		}
		return subs;
	}
}
