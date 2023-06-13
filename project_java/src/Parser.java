import java.util.Comparator;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Parser {
    public static void parser(){
        String linha;

    }

    public Map<String,User> parseUsers(String filename){
        Map<String,User> users = new TreeMap<>(Comparator.naturalOrder());
        Scanner sc = new Scanner(filename);
        while(sc.hasNext()) {
            String[] linhas = sc.nextLine();
        }
    }
}


/*
    Seja qual for o tipo de ficheiro que vamos querer fazer o parsing temos que :
        1. Abrir o ficheiro
        2. Passar o ficheiro ao Scanner
        3. Guardar uma linha válida num array de Strings
        4. Separar os campos e colocar no lugar correto.
*/