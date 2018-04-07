#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define FALSE 0
#define TRUE 1

int n, message_length,flag,j;

int Make_Public_Key(long e_pi);
int Make_Private_Key(int e, long e_pi);

int IsNotPrime(int n);
// check for prime numbers
long Make_Random_Prime_Number();
// random prime number (2) generator
long mod(long n, long e, long m);	//
int Make_Cyper_text(char *Plain_text, long *Cyper_text, int key);
// Function to make plain text passphrase
int Make_Plain_text(long *Cyper_text, char *Plain_text, int key); 
// Functions that make the ciphertext plain
int GCD(long x, long y)		// check the greatest common divisor
{ 	return y == 0 ? x : GCD(y, x % y) ;  } 

void main(void)
{
	long send_msg[100];
	char recv_msg[100], buffer[100];
	int public_key, private_key;
	long m;
	m = Make_Random_Prime_Number();	
	// Create two decimals and get the value of the global variable n. 
	public_key = Make_Public_Key (m);	
	// Create the public key.
	private_key = Make_Private_Key (public_key, m);
	// Create the private key. 
	printf("m=%d, n=%d, public_key=%d, private_key=%d\n\n", m, n, public_key, private_key);

	printf("\nWrite Sentence = ");
	scanf(" %s",buffer);
	printf("\nBuffer Storage = %s \n", buffer);

	Make_Cyper_text(buffer, send_msg, public_key);
	Make_Plain_text(send_msg, recv_msg, private_key);
	printf("\nTranslation Sentenec = %s \n", recv_msg);
}
int prime(long int pr) {
	int i;
	j = sqrt(pr);
	for (i = 2; i <= j; i++) {
		if (pr%i == 0)
			return 0;
	}
	return 1;
}

long Make_Random_Prime_Number()
// random prime number (2) generator
{
	int i;
	int Prime[2];
	// P and Q The two prime numbers are the public key, the base prime of the secret key
	time_t t;
	srand((unsigned int) time(&t)); // Create a random number
	for (i=0; i<2; i++)				// Create two arbitrary primes P and Q 
	{
		do{
		Prime[i]=rand()%100+11;
		}while(IsNotPrime(Prime[i]) );	 
		// Repeat if it is not a decimal number.
	}
	n=Prime[0]*Prime[1];
	// Generate n values ??using two prime numbers p and q
	printf("\nP=%d, Q=%d m=%d n=%d \n", Prime[0], Prime[1], n);
	return (Prime[0]-1)*(Prime[1]-1);  
	// Euler pie value;
}


int Make_Public_Key(long e_pi)
{
	long e;
	do
	{
		e=rand()%100;	
		if ( (e<e_pi) && (GCD(e,e_pi)==1) ) return e;
		// Return E to the Euler pie.
	}while(1);
}

int Make_Private_Key(int e, long e_pi)
{
	int d=0;
	while (((e*d)%e_pi)!=1) d++;		
	// Create private key
	return d;
	// return the private key. 
}


int IsNotPrime(int n)
// check if it is not a decimal number
{
   int  i, limit;
   if (!(n%2))  return (TRUE);
   // Not even if it is an even number.
   limit = (int)sqrt(n) +1;	// Find the decimal number faster by n squared +1.
   for (i = 3; i <= limit; i += 2) 
	   // Perform the remainder operation in odd units from 3 
      if (!(n%i))  return (TRUE); 
   return (FALSE);
}

long mod(long n, long e, long m)
// perform residue = n ^ e (mod m)
{
	long i, residue = 1;
	for(i=1; i<=e; i++)
	{
		residue *= n;	//residue=residue*n
		residue %= m;	
	}
	// residue = residue% n Decrease the number of digits using the mod operation to prevent overflow.
	return residue;
}


int Make_Cyper_text(char *Plain_text, long *Cyper_text, int key)
{
	int i;
	message_length=strlen(Plain_text);
	for(i=0; i<message_length; i++)	  
		// Repeat to the length of the message.
		Cyper_text[i]= (long)mod( Plain_text[i], key, n);
	//encryption
	Cyper_text[i] = '\0';
	// End mark
	printf("====================================================\n");
	printf("Encryption Data = ");	
	for ( i=0; i<message_length; i++)		
		printf(" %d ",Cyper_text[i]);
	// Output the encrypted data.
	printf("\n");	
	return 0;
}

int Make_Plain_text(long *Cyper_text, char *Plain_text, int key)
{
	int  i;
	for(i=0; i<message_length; i++)
		// Repeat to the length of the message.
		Plain_text[i]= (char)mod(Cyper_text[i], key, n);
	// Decrypt
	Plain_text[i] = '\0';
	printf("receive message = ");
	for(i=0; i<message_length; i++)	
		printf(" %d ", Plain_text[i]);
	// Output the decoded data.
	printf("\n");	
	return 0;
}
