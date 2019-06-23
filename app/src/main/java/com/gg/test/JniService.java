package com.gg.test;

import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;

public class JniService extends BaseService{
    private ChildListener childListener;
    @Override
    public IBinder onBind(Intent intent) {
        return new JniBind(this);
    }

    @Override
    protected void click() {
        try {
            childListener.childResult("品牌和技术");
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void setListener(ChildListener var0) {
        childListener = var0;
    }


}
