package com.gg.test;

import android.os.RemoteException;

public class JniBind extends ServiceInterface.Stub {
    private final BaseService bs;

    public JniBind(BaseService var0) {
        bs = var0;
    }

    @Override
    public void click() throws RemoteException {
        bs.click();
    }

    @Override
    public void setJniListener(ChildListener var0) throws RemoteException {
        bs.setListener(var0);
    }
}
