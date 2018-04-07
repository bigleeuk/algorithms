import java.util.Scanner;
public class distinctSub {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		System.out.println("How many testing do U want");
		int count=scan.nextInt();
		System.out.println("Simple Input");	
		int i=0;
		int result=0;
		while(true) {
			//mess1 : receive String , mess2 : enter your String
			String mess1,mess2;
			mess1= scan.next();
			mess2= scan.next();
			//result is recall instance 
			result=Distinct_Subsequence(mess1,mess2);
			System.out.println("Simple Output");
			System.out.println(result);
			i++;
			//count instance : how many u want testing
			if(i==count)
				break;
		}

	}
	// Distinct_Subsequence : Find the number of possible combinations of words.
	public static int Distinct_Subsequence(String msg1, String msg2) {
		int m1 = msg1.length();
		int m2 = msg2.length();
		//Reason for doing length + 1: To set the part of the first matrix to 1.
		//This is because if the mess1 and mess2 are the same number in the algorithm configuration, it should be 1.
		int depu[][] = new int[m1+1][m2+1];
		//If mess1 and mess2 are the same,1 should be output.
		for(int i=0; i<=m1;i++){
			depu[i][0] = 1;
		}
		/*
		depu(i, j) = number of occurrences of a up to the i-th string of a in the partial string up to the j-th string of b
		if ) a[i] == b[j] ,depu(i, j) = depu(i, j - 1) + depu(i - 1, j - 1)
		if ) a[i] != b[j] , depu(i, j) = depu(i, j - 1)
		*/
		for(int i=1; i<=m1; i++){
			for(int j=1; j<=m2; j++){
				if(msg1.charAt(i-1) == msg2.charAt(j-1)){
					depu[i][j] += depu[i-1][j]+depu[i-1][j-1];
				}else{
					depu[i][j] +=depu[i-1][j];
				}
			}
		}
		/*If you create a matrix in the above way, you can see that the number increases depending on the number of cases.
		Also, the last index value of the matrix is ​​the maximum number.
		*/
		return depu[m1][m2];
	}
}