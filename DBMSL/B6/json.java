import com.mongodb.*;

import org.bson.Document;
import org.json.simple.*;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;

public class json {

    public static void main(String[] args)  {
      
        JSONObject obj=new JSONObject();  
        obj.put("name","ABC");  
        obj.put("age",new Integer(19));  
        obj.put("salary",new Double(60000));  
        System.out.print(obj);  
        
        JSONArray arr = new JSONArray();
        arr.add(obj);
        
        try{
        MongoClient mongo = new MongoClient("10.10.13.51",27017);
        MongoCredential credential;
        credential = MongoCredential.createCredential("te3177","te3177db","te3177".toCharArray());
        System.out.println("Connected to the database successfully");
    
        MongoDatabase database = mongo.getDatabase("te31db71");
        System.out.println("Credentials ::"+ credential);
       
        MongoCollection collection = database.getCollection("sampleCollection");
       
        Document doc = Document.parse(obj.toString());
        collection.insertOne(doc);
       
        FindIterable<Document> docs = collection.find();
        if (docs == null) {
            System.out.println("Not found");
        }

        for(Document doc1 : docs) {
            System.out.println(doc1);
        }
       
        System.out.println("Done");
        mongo.close();
        }
        catch(MongoException e){
            e.printStackTrace();
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
  

}


