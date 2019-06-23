// ServiceInterface.aidl
package com.gg.test;

// Declare any non-default types here with import statements
import com.gg.test.ChildListener;
interface ServiceInterface {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    void click();
    void setJniListener(ChildListener var0);
}
