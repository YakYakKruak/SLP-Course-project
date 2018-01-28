package frontend.controller;

import frontend.jni.JniHelper;
import frontend.utils.Point;
import javafx.embed.swing.SwingFXUtils;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;

import javax.imageio.ImageIO;
import java.io.File;

import static java.lang.Math.sqrt;

public class PaintController {

    @FXML
    private Canvas canvasTrack;

    @FXML
    private Canvas canvas;

    @FXML
    private ColorPicker colorPicker;

    @FXML
    private TextField brushSize;

    @FXML
    private CheckBox eraser;

    private GraphicsContext g;

    private JniHelper manager = JniHelper.getInstance();


    public void initialize() {
        GraphicsContext g2 = canvasTrack.getGraphicsContext2D();
        g = canvas.getGraphicsContext2D();

        Thread painter = new Thread(() -> {
            double prevX = 0;
            double prevY = 0;
            double size = Double.parseDouble(brushSize.getText());
            g2.setFill(Color.WHITE);

            while (true) {
                if (brushSize.getText().matches("[0-9]+"))
                    size = Double.parseDouble(brushSize.getText());
                g.setLineWidth(size);
                Point point = manager.getPoint();
                double x = point.getX();
                double y = point.getY();
                x = 640 - x;
                g2.clearRect(prevX, prevY, 10, 10);
                g2.fillOval(x, y, 10, 10);

                if (point.isClick()) {
                    if (prevX != 0 && prevY != 0 && sqrt((prevX - x) * (prevX - x) + (prevY - y) * (prevY - y)) < 100) {
                        if (!eraser.isSelected()) {
                            g.setStroke(Paint.valueOf(colorPicker.getValue().toString()));
                            g.moveTo(prevX, prevY);
                            g.lineTo(x, y);
                            g.stroke();
                            g.beginPath();
                        } else {
                            g.clearRect(x, y, size, size);
                        }
                    }
                }
                prevX = x;
                prevY = y;
            }
        });
        painter.setDaemon(true);
        painter.start();
    }

    public void onSave() {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        try {
            Image snapshot = canvas.snapshot(null, null);
            ImageIO.write(SwingFXUtils.fromFXImage(snapshot, null), "png", new File("paint.png"));
            alert.setContentText("Image saved");

        } catch (Exception e) {
            alert.setAlertType(Alert.AlertType.ERROR);
            alert.setContentText("Failed to save image: " + e);
        }
        alert.showAndWait();
    }

    public void recognizeText(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        try {
            Image snapshot = canvas.snapshot(null, null);
            ImageIO.write(SwingFXUtils.fromFXImage(snapshot, null), "png", new File("paint.png"));
            String recognized = manager.recognizeText();

            if(recognized.length() > 0){
                alert.setTitle("Recognized text");
                alert.setHeaderText("Recognized text from snaphot");
                alert.setContentText(manager.recognizeText());
            } else {
                alert.setAlertType(Alert.AlertType.ERROR);
                alert.setContentText("Can't recognize any text");
            }

            alert.showAndWait();
        } catch (Exception e){
            alert.setAlertType(Alert.AlertType.ERROR);
            alert.setContentText("Failed to save image: " + e);
            alert.showAndWait();
        }
    }

    public void clear (){
        g.clearRect(0,0,640,480);
    }

    public void onExit() {
        manager.close();
    }
}
