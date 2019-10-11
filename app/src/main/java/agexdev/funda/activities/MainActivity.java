package agexdev.funda.activities;

import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageButton;

import agexdev.funda.R;

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

public class MainActivity extends AppCompatActivity {

    private MediaPlayer mediaPlayer;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);


        ImageButton btnPlay = (ImageButton) findViewById(R.id.imageButton);

        btnPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent playintent = new Intent(getApplicationContext(), CSDL2Activity.class);
                startActivity(playintent);
            }
        });

        mediaPlayer = MediaPlayer.create(this, R.raw.cave);
        mediaPlayer.start();
        mediaPlayer.setLooping(true);

    }

    @Override
    public void onBackPressed() {
        mediaPlayer.stop();
        mediaPlayer.release();
        finish();
    }
}
