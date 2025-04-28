import java.sql.*;
public class BankAnalysis {
    public static void main(String[] args) throws ClassNotFoundException {
        String url = "jdbc:oracle:thin:@localhost:1521:xe";
        String username = "ID220041154";
        String password = "cse4308";
        String query = "SELECT ACCOUNT_ID, amount, type " +
                "FROM TRANSACTIONS " +
                "ORDER BY ACCOUNT_ID ASC";
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
            System.out.println("Drivers loaded successfully");
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }

        try {
            Connection con = DriverManager.getConnection(url, username, password);
            System.out.println("Connection established successfully!!");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            if (!rs.next()) {
                System.out.println("no results found ");
            }
            int total_numbers[] = new int[100];
            int total_transaction[] = new int[100];
            while (rs.next()) {
                int account_id = rs.getInt(1);
                int amount = rs.getInt(2);
                int accoun_type = rs.getInt(3);
                //System.out.println(accoun_type);
                if (accoun_type == 0) {
                    total_numbers[account_id - 1] += amount;
                } else {
                    total_numbers[account_id - 1] -= amount;
                }
                total_transaction[account_id - 1] += amount;
            }
            int cip = 0;
            int vip = 0;
            int op = 0;
            int not_chatagorizied = 0;
            for (int i = 0; i < 100; i++) {
                if (total_numbers[i] > 1000000 && total_transaction[i] > 5000000) {
                    cip++;
                } else if ((total_numbers[i] > 500000 && total_numbers[i] < 900000) && (total_transaction[i] > 2500000 && total_transaction[i] < 4500000)) {
                    vip++;
                } else if (total_numbers[i] < 100000 && total_transaction[i] < 1000000) {
                    op++;
                } else {
                    not_chatagorizied++;
                }
            }
            System.out.println("cip : " + cip);
            System.out.println("vip : " + vip);
            System.out.println("op : " + op);
            System.out.println("not_catagorized : " + not_chatagorizied);
            rs.close();
            String query2 = "SELECT ACCOUNT_ID,sum(AMOUNT),TRANSACTION_DATE " +
                    "FROM TRANSACTIONS " +
                    "group by ACCOUNT_ID,TRANSACTION_DATE " +
                    "HAVING  EXTRACT(MONTH FROM SYSDATE)-EXTRACT(MONTH FROM transaction_date) =1 " +
                    "ORDER by ACCOUNT_ID asc ";
            ResultSet rs2 = stmt.executeQuery(query2);
            while (rs2.next())
            {
                int account_id = rs2.getInt(1);
                int sum = rs2.getInt(2);
                if (sum >=10000)
                {
                    System.out.println("account id : "+account_id+" amount : "+sum);
                }
            }
            rs2.close();
            ResultSet rs3 = stmt.executeQuery("SELECT * from (select transaction_date, count(*) from TRANSACTIONS " +
                    "WHERE AMOUNT > (select avg(AMOUNT) from TRANSACTIONS) " +
                    "group by transaction_date " +
                    "order by COUNT(*) DESC) " +
                    "where ROWNUM =1 ");
            while (rs3.next()){
                Date d1 = rs3.getDate(1);
                int count = rs3.getInt(2);
                System.out.println("date : "+d1+" count : "+count);
            }
            ResultSet rs4 = stmt.executeQuery("select * from Account");
            ResultSet rs5 = stmt.executeQuery("select * from TRANSACTIONS");
            ResultSetMetaData rsmd = rs5.getMetaData();
            ResultSetMetaData rsmd2 = rs5.getMetaData();
            for (int i = 1; i <= rsmd.getColumnCount(); i++) {
                System.out.println(rsmd.getColumnName(i));
                System.out.println(rsmd.getColumnTypeName(i));
            }
            stmt.executeQuery("DROP TABLE ACCOUNT CASCADE CONSTRAINTS");
            stmt.executeQuery("DROP TABLE TRANSACTIONS CASCADE CONSTRAINTS");
            con.commit();
            rs4.close();
            rs5.close();
            rs3.close();
            stmt.close();
            con.close();
            System.out.println("system closed successfully");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}