package agexdev.funda;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * This file and its content is copyright of Age-X Development - © 2017. All rights reserved.
 * Any redistribution or reproduction of part or all of the contents in any form is prohibited.
 * you may not print or download to a local hard disk extracts for your personal or non-commercial use.
 * you may not copy the content to individual third parties for their personal use the source of the material.
 * You may not, except with our express written permission, distribute or commercially exploit the content.
 * Nor may you transmit it or store it in any other website or other form of electronic retrieval system.
 *
 * @author Van Lee Chigwada
 * @author vanleechigwada@gmail.com
 * @author agexdev.com
 */


public class FileUtils {

    private static BufferedReader reader;

    public static Bitmap getBitmapFromAssets(Context ctx, String fileName) {

        AssetManager assetManager = ctx.getAssets();

        InputStream istr;
        try {
            istr = assetManager.open(fileName);

            Bitmap bitmap = BitmapFactory.decodeStream(istr);

            return bitmap;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static String[] getLinesFromFile(Context ctx, String filename) {

        String[] lines = null;
        ArrayList<String> _lines = new ArrayList<String>();

        try {
            reader = new BufferedReader(new InputStreamReader(ctx.getAssets().open(filename)));

            String line = null;
            while ((line = reader.readLine()) != null) {

                _lines.add(line);
            }

            lines = _lines.toArray(new String[_lines.size()]);

        } catch (IOException e) {
        } finally {
            if (reader != null) {
                try {
                    reader.close();

                } catch (IOException e) {
                }
            }
        }

        return lines;
    }

    public static List<String> getLinesFromFileAsList(Context ctx, String filename) {

        List<String> lines = null;
        ArrayList<String> _lines = new ArrayList<String>();

        try {
            reader = new BufferedReader(new InputStreamReader(ctx.getAssets().open(filename)));

            String line = null;
            while ((line = reader.readLine()) != null) {

                _lines.add(line);
            }

            lines = _lines;

        } catch (IOException e) {
        } finally {
            if (reader != null) {
                try {
                    reader.close();

                } catch (IOException e) {
                }
            }
        }

        return lines;
    }

    public static List<String> getFilenamesFromAssetsFolder(Context ctx, String foldername) {
        List<String> names = new ArrayList<String>();


        AssetManager assetManager = ctx.getAssets();

        try {
            String files[] = assetManager.list(foldername);

            names = Arrays.asList(files);

        } catch (IOException e) {
            Log.e(ctx.getString(R.string.app_name), e.getMessage());
        }

        return names;
    }
}
