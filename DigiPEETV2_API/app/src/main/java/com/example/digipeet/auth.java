package com.example.digipeet;

public class auth {

    private String acess_token;

    public String getacess_token() {
        return acess_token;
    }

    public void setacess_token(String acess_token) {
        this.acess_token = acess_token;
    }

    public String getrefresh_token() {
        return refresh_token;
    }

    public void setrefresh_token(String refresh_token) {
        this.refresh_token = refresh_token;
    }

    private String refresh_token;

    public auth(String acess_token, String refresh_token){
        this.acess_token = acess_token;
        this.refresh_token = refresh_token;

    }

}
