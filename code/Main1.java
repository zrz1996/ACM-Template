import java.io.*;
import java.util.*;
import java.math.*;
public class Main1
{
	static BigInteger C[][] = new BigInteger[110][110];

	public static void main(String[] args) throws IOException
	{
		/*C[0][0] = BigInteger.ONE;
		for (int i = 1; i < 110; i++)
		{
			C[i][i] = C[i][0] = BigInteger.ONE;
			for (int j = 1; j < i; j++)
				C[i][j] = C[i-1][j].add(C[i-1][j-1]);
		}
		Scanner cin = new Scanner(System.in);
		BigInteger n;
		int k;
		BigInteger A[] = new BigInteger[110];
		while (cin.hasNext())
		{
			n = cin.nextBigInteger();
			k = cin.nextInt();
			A[0] = n;
			for (int i = 1; i <= k; i++)
			{
				A[i]=n.add(BigInteger.ONE).pow(i+1);
				A[i] = A[i].subtract(BigInteger.ONE);
				for (int j = 2; j <= i+1; j++)
					A[i] = A[i].subtract(C[i+1][j].multiply(A[i-j+1]));
				A[i] = A[i].divide(BigInteger.valueOf(i+1));
			}
			System.out.println(A[k]);
		}*/
		Scanner cin = new Scanner(System.in);
		BigDecimal a;
		BigDecimal b;
		BigDecimal c;
		BigInteger n;
		while (cin.hasNext())
		{
			a = cin.nextBigDecimal();
			b = cin.nextBigDecimal();
			//b = cin.nextBigDecimal();
			//c = a.mod(b);
			/*if (a.compareTo(b) == -1)
				c = a;
			else c = b;*/
			c = a.divide(b);
			if (c.compareTo(BigDecimal.ZERO) == -1)
				c = c.multiply(new BigDecimal(-1));
			System.out.println(c.toPlainString());
		}
	}
}

