package penchev.vladislav.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.JsonObject;

import penchev.vladislav.myapplication.retrofit.ApiCallInterface;
import penchev.vladislav.myapplication.retrofit.RetrofitUtil;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button off = findViewById(R.id.off);
        Button on = findViewById(R.id.on);

        Button esp = findViewById(R.id.espUrl);

        final ApiCallInterface apiCallInterface = RetrofitUtil.getApiCallInterface();

        on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                apiCallInterface.on().enqueue(new Callback<JsonObject>() {
                    @Override
                    public void onResponse(Call<JsonObject> call, Response<JsonObject> response) {
                        Toast.makeText(MainActivity.this, "Successful on", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onFailure(Call<JsonObject> call, Throwable t) {
                        Toast.makeText(MainActivity.this, "Fail on", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });

        off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                apiCallInterface.off().enqueue(new Callback<JsonObject>() {
                    @Override
                    public void onResponse(Call<JsonObject> call, Response<JsonObject> response) {
                        Toast.makeText(MainActivity.this, "Successful off", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onFailure(Call<JsonObject> call, Throwable t) {
                        Toast.makeText(MainActivity.this, "Fail off", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        
    }
}
