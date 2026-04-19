import com.google.gson.*;
import java.io.*;
import java.util.*;

class Transaction {
    String transaction_id;
    int amount;
}

public class Transacciones {

    public static void main(String[] args) {
        String inputFile = "transaction_data.json";
        String outputFile = "ResultadoSinDuplicados.json";

        try {
            Reader reader = new FileReader(inputFile);
            JsonArray jsonArray = JsonParser.parseReader(reader).getAsJsonArray();

            Set<String> seen = new HashSet<>();
            JsonArray result = new JsonArray();

            for (JsonElement element : jsonArray) {
                JsonObject obj = element.getAsJsonObject();

                String id = obj.get("transaction_id").getAsString();

                if (!seen.contains(id)) {
                    seen.add(id);
                    result.add(obj);
                }
            }
            
            Gson gson = new GsonBuilder().setPrettyPrinting().create();
            Writer writer = new FileWriter(outputFile);
            gson.toJson(result, writer);

            writer.close();
            reader.close();

            System.out.println("Archivo generado: " + outputFile);

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}