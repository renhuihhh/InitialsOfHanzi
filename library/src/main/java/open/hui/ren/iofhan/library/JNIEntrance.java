package open.hui.ren.iofhan.library;

/**
 * @author renhui
 * @date 16-9-13
 * @desc open.hui.ren.library
 */
public class JNIEntrance {

    static {
        boolean success = false;
        try {
            System.loadLibrary("jni_entrance");
            success = true;
        } catch (Throwable e) {
            success = false;
        }
    }


    public synchronized static native String welcom2NdkWorld(int n);

    public synchronized static native String getStringInitials(String s);
}

