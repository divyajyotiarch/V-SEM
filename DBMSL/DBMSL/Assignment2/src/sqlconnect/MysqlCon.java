package sqlconnect;

import java.sql.*;  

class MysqlCon{  
public static void main(String args[]){  
try{  
	Class.forName("com.mysql.jdbc.Driver");  
	Connection con=DriverManager.getConnection(  
	"jdbc:mysql://10.10.12.76:3306/t3177db","t3177","t3177");  
	
	Statement stmt=con.createStatement();  
//complexView	int rs=stmt.executeUpdate("create view view1 as select prof.prof_id,prof_fname,salary from prof,shift where prof.prof_id=shift.prof_id");  

//step2:	int rs=stmt.executeUpdate("create index index_prof on prof(prof_id)"); 

	//	int rs=stmt.executeUpdate("create unique index index_dept on prof(prof_id)"); 

	//	int rs=stmt.executeUpdate("drop index index_dept on prof");
	
	//int rs=stmt.executeUpdate("drop view view2");
	
//simpleView  int rs=stmt.executeUpdate("create view view2 as select prof.prof_id,prof_fname,salary from prof"); 
	
/*	ResultSet rss=stmt.executeQuery("show index from prof");
	while(rss.next())  
		System.out.println(rss.getString(1)+"  "+rss.getString(2)+"  "+rss.getString(3)+"  "+rss.getString(4)); 
	*/
//sequence  int rs=stmt.executeUpdate("alter table shift add seq1 int primary key not null auto-increment first")
	ResultSet rss=stmt.executeQuery("select * from view2");
	while(rss.next())  
		System.out.println(rss.getInt(1)+"  "+rss.getString(2)+"  "+rss.getString(3)); 
	con.close();  
}catch(Exception e){ System.out.println(e);}  
}  
}