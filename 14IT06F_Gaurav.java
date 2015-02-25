import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
public class PortScan {
public static void main(String args[]) throws IOException
{
int startPortRange=1;
int stopPortRange=1024;
BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

System.out.println("Enter the IP Addressof the host u want to scan:");
String ipAddr=br.readLine();

System.out.println("Open ports are in:"+ipAddr+" are:");
for(int i=startPortRange; i <=stopPortRange; i++)
{
try
{
Socket ServerSok = new Socket(ipAddr,i);
System.out.println( i );
ServerSok.close();
}
catch (Exception e)
{
//System.out.println("Port not in use: " + i );
}
}
}
}
