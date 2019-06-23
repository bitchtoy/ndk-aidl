package com.gg.test;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;

//所有功能，统一对外接口
public class Proxy {
    //单例模式
    private static Proxy instance = null;
    //是否绑定服无
    private boolean isBindService = false;
    //是否初始化是否成功
    private boolean isInit = false;
    private ServiceInterface anInterface;

    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
         anInterface = ServiceInterface.Stub.asInterface(service);
         isBindService = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
          anInterface = null;
          isBindService = false;

        }
    };
    //单例模式，唯一功能对外开放接口
    public  static Proxy getInstance(){
        if (instance == null){
            Class var0 = Proxy.class;
            synchronized (var0){
                if (instance == null){
                    instance = new Proxy();
                }
            }
        }
        return instance;
    }
    //绑定服务
    public void bindService(Context cxt){
        Intent var0 = new Intent(cxt,JniService.class);
        cxt.bindService(var0,connection, Service.BIND_AUTO_CREATE);
    }
    //是否绑定服务
    public boolean isBindServiced(){
        return isBindService;
    }
    //是否初始化
    public boolean isInited(){
        if (!isInit){
            isInit = isBindService;
        }
        return isInit;
    }
    public void jni(){
        if (isInited()){
            try {
                anInterface.click();
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }
     public void setJniListener(ChildListener listener){
        if (isInited()){
            try {
                anInterface.setJniListener(listener);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

     }
}
