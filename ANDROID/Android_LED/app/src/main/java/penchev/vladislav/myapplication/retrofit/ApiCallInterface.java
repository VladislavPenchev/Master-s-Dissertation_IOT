package penchev.vladislav.myapplication.retrofit;

import com.google.gson.JsonObject;

import retrofit2.Call;
import retrofit2.http.GET;

public interface ApiCallInterface {

    // Base url
    String BASE_URL = "http://192.168.0.104/5/";

    @GET("off")
    Call<JsonObject> off();

    @GET("on")
    Call<JsonObject> on();

    @GET("")
    Call<JsonObject> esp();

}
