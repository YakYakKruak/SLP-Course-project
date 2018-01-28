package frontend.jni;


import frontend.utils.Point;

public class JniHelper {

    static {
        System.loadLibrary("ps");
    }

    private static JniHelper ourInstance = new JniHelper();

    public static JniHelper getInstance() {
        return ourInstance;
    }

    private JniHelper() {
        int res = init0();
        if(res != 0)
            throw new RuntimeException("Can't initialize move or recognizer");
    }

    public Point getPoint() {
        int points[] = getPoint0();

        if(points == null) {
            throw new OutOfMemoryError("Сan't allocate memory for a point");
        }

        boolean clicked = points[2] > 0; //if trigger > 0;
        return new Point(points[0],points[1],clicked);
    }

    public String recognizeText() {
        String recognized = recognize0();
        if(recognized != null)
            return recognized;
        else return "";
    }

    public void close() {
        close0();
    }

    private native String recognize0();

    private native void close0();

    private native int init0();

    private native int[] getPoint0();

}
