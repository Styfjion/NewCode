import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Collectors;

/**
 * ReadFile
 */
public class ReadFile {

    public static void main(String[] args) {
        var path = Paths.get("test.env");
        try {
            var result = Files.readAllLines(path);
            var ret = result.stream().map(u -> u.split("=")[0]).collect(Collectors.joining(","));
            System.out.println(ret);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
