#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>

using namespace std;

//Parameters
int nr_of_lines = 2500;
int percentage_of_Enc_Dec = 100; 
int percentage_of_Enc_Dec_Row = 100;
bool two_address_mode = false;
bool row = false;
bool no_enc = false;
bool rowenc = false;

int nr_of_writes = 0;
int nr_of_reads = 0;
int nr_of_encrypts = 0;
int nr_of_decrypts = 0;
int nr_of_encrypt_rows = 0;
int nr_of_decrypt_rows = 0;

void generate_line(char* line);

void generate_command(char* cmd);

void generate_addr(char* addr);

int main(){

	srand(time(NULL));
	cout << "Enter number of lines: ";
	cin >> nr_of_lines;
	cout << "Enc/Dec?";
	cin >> no_enc;
	cout << "Row?";
	cin >> rowenc;
	if(no_enc){
	cout << "Enter percentage of Enc/Dec: ";
	cin >> percentage_of_Enc_Dec;
	if(rowenc){
	cout << "Enter percentage of these Enc/Dec being Enc/Dec-Row: ";
	cin >> percentage_of_Enc_Dec_Row;
	}
	cout << "Two address mode(1/0): ";
	cin >> two_address_mode;
	}	

	ofstream outputFile;
	outputFile.open("./Desktop/ramulator-safari-dev/dram.trace");

	char current_line[25];

	for(int i = 0; i < nr_of_lines-1; i++){
		generate_line(current_line);
		outputFile << current_line << endl;
			}


	generate_line(current_line);
	outputFile << current_line;
	outputFile.close();

	cout << "Number of Reads: " << nr_of_reads << endl;
	cout << "Number of Writes: " << nr_of_writes << endl;
	cout << "Number of Encrypts: " << nr_of_encrypts << endl;
	cout << "Number of Decrypts: " << nr_of_decrypts << endl;
	cout << "Number of Encrypt Row: " << nr_of_encrypt_rows << endl;
	cout << "Number of Decrypt Row: " << nr_of_decrypt_rows << endl;



	return 0;
}

void generate_line(char* line){

	char command[2];
	char addr[8];

	if(!no_enc){
		generate_command(command);
		generate_addr(addr);
			line[0] = '0';
			line[1] = 'x';
			line[2] = addr[0];
			line[3] = addr[1];
			line[4] = addr[2];
			line[5] = addr[3];
			line[6] = addr[4];
			line[7] = addr[5];
			line[8] = addr[6];
			line[9] = addr[7];
			line[10] = ' ';
			line[11] = command[0]; 
			line[12] = '\0';
	} else {
	if(two_address_mode){
		generate_command(command);
		if(command[0] == 'R' || command[0] == 'W'){
			generate_addr(addr);
			line[0] = '0';
			line[1] = 'x';
			line[2] = addr[0];
			line[3] = addr[1];
			line[4] = addr[2];
			line[5] = addr[3];
			line[6] = addr[4];
			line[7] = addr[5];
			line[8] = addr[6];
			line[9] = addr[7];
			line[10] = ' ';
			line[11] = command[0]; 
			line[12] = '\0';
		} else {
			generate_addr(addr);
				line[0] = '0';
				line[1] = 'x';
				line[2] = addr[0];
				line[3] = addr[1];
				line[4] = addr[2];
				line[5] = addr[3];
				line[6] = addr[4];
				line[7] = addr[5];
				line[8] = addr[6];
				line[9] = addr[7];
				line[10] = ' ';
				line[11] = command[0]; 
				if(row){
					line[12] = command[1];
					generate_addr(addr);

					line[13] = ' ';
					line[14] = '0';
					line[15] = 'x';
					line[16] = addr[0];
					line[17] = addr[1];
					line[18] = addr[2];
					line[19] = addr[3];
					line[20] = addr[4];
					line[21] = addr[5];
					line[22] = addr[6];
					line[23] = addr[7];
					line[24] = '\0';
					row = false;
				} else {
					generate_addr(addr);

					line[12] = ' ';
					line[13] = '0';
					line[14] = 'x';
					line[15] = addr[0];
					line[16] = addr[1];
					line[17] = addr[2];
					line[18] = addr[3];
					line[19] = addr[4];
					line[20] = addr[5];
					line[21] = addr[6];
					line[22] = addr[7];
					line[23] = '\0';
				}
		}
	} else {
		generate_command(command);
		generate_addr(addr);
			line[0] = '0';
			line[1] = 'x';
			line[2] = addr[0];
			line[3] = addr[1];
			line[4] = addr[2];
			line[5] = addr[3];
			line[6] = addr[4];
			line[7] = addr[5];
			line[8] = addr[6];
			line[9] = addr[7];
			line[10] = ' ';
			line[11] = command[0]; 
			if(row){
				line[12] = command[1];
				line[13] = '\0';
				row = false;
			} else {
				line[12] = '\0';
			}
	}
	}

}

void generate_command(char* cmd){

	if(!no_enc){
		int random = rand() % 2;
			switch(random){
			case 0:
				cmd[0] = 'R';
				nr_of_reads++;
				break;
			case 1: 
				cmd[0] = 'W';
				nr_of_writes++;
				break;
			default: 
				cmd[0] = 'R';
				nr_of_reads++;

		}
	} else {
		int ratio = 100/percentage_of_Enc_Dec;
		int ratio2 = 100/percentage_of_Enc_Dec_Row;

		int enc_dec = rand() % ratio;
		int enc_dec_row = rand() % ratio2;
		int random = rand() % 2;


		int randomnr = rand() % 100;

		if(randomnr < percentage_of_Enc_Dec){
			switch(random){
				case 0:
					if(enc_dec_row == 0 && rowenc){
						cmd[0] = 'E';
						cmd[1] = 'R';
						nr_of_encrypt_rows++;
						row = true;
						break;
					} else {
						cmd[0] = 'E';
						nr_of_encrypts++;
						break;
					}
				case 1: 
					if(enc_dec_row == 0 && rowenc){
						cmd[0] = 'D';
						cmd[1] = 'R';
						nr_of_decrypt_rows++;
						row = true;
						break;
					} else {
						cmd[0] = 'D';
						nr_of_decrypts++;
						break;
					}
				default: 
					cmd[0] = 'E';
					nr_of_encrypts++;
			}	
		} else {
			switch(random){
				case 0:
					cmd[0] = 'R';
					nr_of_reads++;
					break;
				case 1: 
					cmd[0] = 'W';
					nr_of_writes++;
					break;
				default: 
					cmd[0] = 'R';
					nr_of_reads++;

			}
		}
/*
	if(enc_dec == 0){
		switch(random){
			case 0:
				if(enc_dec_row == 0 && rowenc){
					cmd[0] = 'E';
					cmd[1] = 'R';
					nr_of_encrypt_rows++;
					row = true;
					break;
				} else {
					cmd[0] = 'E';
					nr_of_encrypts++;
					break;
				}
			case 1: 
				if(enc_dec_row == 0 && rowenc){
					cmd[0] = 'D';
					cmd[1] = 'R';
					nr_of_decrypt_rows++;
					row = true;
					break;
				} else {
					cmd[0] = 'D';
					nr_of_decrypts++;
					break;
				}
			default: 
				cmd[0] = 'E';
				nr_of_encrypts++;
		}
	} else {
		switch(random){
			case 0:
				cmd[0] = 'R';
				nr_of_reads++;
				break;
			case 1: 
				cmd[0] = 'W';
				nr_of_writes++;
				break;
			default: 
				cmd[0] = 'R';
				nr_of_reads++;

		}
	}
	*/
	}
}


void generate_addr(char* addr){

	
	for(int i = 0; i < 8; i++){	
		int x = rand() % 16;
		char intermediate;

		switch(x){
			case 0:
				intermediate = '0';
				break;
			case 1:
				intermediate = '1';
				break;
			case 2:
				intermediate = '2';
				break;
			case 3:
				intermediate = '3';
				break;
			case 4:
				intermediate = '4';
				break;
			case 5:
				intermediate = '5';
				break;
			case 6:
				intermediate = '6';
				break;
			case 7:
				intermediate = '7';
				break;
			case 8:
				intermediate = '8';
				break;
			case 9:
				intermediate = '9';
				break;
			case 10:
				intermediate = 'a';
				break;
			case 11:
				intermediate = 'b';
				break;
			case 12:
				intermediate = 'c';
				break;
			case 13:
				intermediate = 'd';
				break;
			case 14:
				intermediate = 'e';
				break;
			case 15:
				intermediate = 'f';
				break;
			
		}

		addr[i] = intermediate;
	}	


}

