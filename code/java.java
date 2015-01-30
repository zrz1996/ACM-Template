import java.io.*;
import java.util.*;
import java.math.*;
public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		int tests = in.nextInt();
		for (int noT = 1; noT <= tests && in.hasNext(); ++noT) (new Task()).solve(noT, in, out);
		out.close();
	}
}
class Task { 
	public void solve(int testNumber, InputReader in, PrintWriter out) { 
		// Implementation here.
	} 
}
class InputReader {
	BufferedReader reader;
	StringTokenizer tokenizer;
	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}
	public boolean hasNext() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) {
				return false;
			}
		}
		return tokenizer.hasMoreTokens();
	}
	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}
}
import java.*;
import java.math.*;
import java.util.*;
public class Main
{
	public static Scanner cin = new Scanner(System.in);
	public static void main(String[] args)
	{
		int n = cin.nextInt();
		BigInteger a[] = new BigInteger[200];
		for (int i = 1; i <= n; i++)
		{
			BigInteger k = cin.nextBigInteger();
			System.out.print("Case "+i+": ");
			a[0] = BigInteger.valueOf(1);
			for (int j = 1; j < 75; j++)
				a[j] = a[j-1].multiply(k);
			BigInteger ans = a[74];
			ans = ans.add(a[38].multiply(BigInteger.valueOf(9)));
			ans = ans.add(a[20].multiply(BigInteger.valueOf(6)));
			ans = ans.add(a[26].multiply(BigInteger.valueOf(8)));
			ans = ans.divide(BigInteger.valueOf(24));
			ans = ans.mod(BigInteger.valueOf(10007));
			System.out.println(ans);
		} 
	}
}
