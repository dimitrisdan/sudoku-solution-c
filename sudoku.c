//Dimitris Danampasis 050097
//Teliki Ergasia

#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc,char *argv[])
{
		
	int sudoku[9][9][9];
	int a[81];
	int loc_matrix[9];
	int itemArray[9];
	int root = 0;
	int i,j,k;
	int flag = -1;
	int tmp;
	int item;
	int grammi;
	int stili;
	int counter;
	int try;
	int plithosMiden;
	
	int myrank;
	int p;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Get_processor_name(processor_name,&namelen);
	
	
	
	
	if(myrank == 0){
		printf("\n\n*******************************************\n");
		printf("==>Dimitris Danampasis\tcs050097@teiath.gr\n==>Teliki ergasia\n==>Eisagwgh ston Parallilo Upologismo");
		printf("\n*******************************************\n\n");
	/* Arxikopoihsh pinaka
	 * O pinakas arxikopoieitai mesa apo to programma kai oxi apo ton xrhsth.
	 * Htan xasimo xronou na prospathw na balw 30 times kathe fora pou to dokimaza. 
	 * Arxika ton gemizw me miden
	 * Meta prosthetw tis arxikes times
	 * Telos gemizw tin trith diastash me arithmous apo 1...9, 
	 * opou den exw balei arxikh timh
	 */
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				for(k=0;k<9;k++)
					sudoku[i][j][k] = 0;
			}
		}
		sudoku[0][2][7] = 8;
		sudoku[0][4][0] = 1;
		sudoku[0][8][8] = 9;
		sudoku[1][0][5] = 6;
		sudoku[1][2][0] = 1;
		sudoku[1][4][8] = 9;
		sudoku[1][6][2] = 3;
		sudoku[1][7][1] = 2;
		sudoku[2][1][3] = 4;
		sudoku[2][4][2] = 3;
		sudoku[2][5][6] = 7;
		sudoku[2][8][4] = 5;
		sudoku[3][1][2] = 3;
		sudoku[3][2][4] = 5;
		sudoku[3][5][7] = 8;
		sudoku[3][6][1] = 2;
		sudoku[4][2][1] = 2;
		sudoku[4][3][5] = 6;
		sudoku[4][4][4] = 5;
		sudoku[4][6][7] = 8;
		sudoku[5][2][3] = 4;
		sudoku[5][5][0] = 1;
		sudoku[5][6][6] = 7;
		sudoku[5][7][4] = 5;
		sudoku[6][0][4] = 5;
		sudoku[6][3][2] = 3;
		sudoku[6][4][3] = 4;
		sudoku[6][7][7] = 8;
		sudoku[7][1][8] = 9;
		sudoku[7][2][6] = 7;
		sudoku[7][4][7] = 8;
		sudoku[7][6][4] = 5;
		sudoku[7][8][5] = 6;
		sudoku[8][0][0] = 1;
		sudoku[8][4][5] = 6;
		sudoku[8][6][8] = 9;
		
		//Ektipwsh Sudoku mono me tis arxikes times
		printf("SUDOKU UNSOLVED :\n");
		flag=0;
		for(i=0;i<9;i++){
			printf("|");
			for(j=0;j<9;j++){
				for(k=0;k<9;k++){
					if(sudoku[i][j][k] != 0) flag=sudoku[i][j][k];tmp=k;
				}
				if (flag != 0)printf("%d\t",flag);
				else printf("\t");
				flag = 0;
			}
			printf("|\n");
		}
		
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				flag=0;
				for(k=0;k<9;k++){
					if(sudoku[i][j][k] != 0) flag=1;
				}
				if(flag == 0){
					for(k=0;k<9;k++) sudoku[i][j][k] = k+1;
				}
			}
		}
		//~Arxikopoihsh pinaka	
	}
	
	// Try einai oi fores pou tha scanarei ton olokliro ton pinaka 
	for(try=0;try<4;try++){
		
		//   Prwta tha afairesei tous arithmous ana grammi
		for(grammi=0;grammi<9;grammi++){
			
			//Ftaixnei ton pinaka a(81 stoixeiwn) tis kathe grammis tou pinaka sudoku 
			if(myrank==0){
				counter=0;											
				for(j=0;j<9;j++){
					for(k=0;k<9;k++){
						a[counter] = sudoku[grammi][j][k];
						counter++;
					}
				}
			}
			
			//Stelnei ton pinaka a ana 9 stis 9 diergasies
			root=0;
			MPI_Scatter(a, 9, MPI_INT, loc_matrix, 9, MPI_INT, root, MPI_COMM_WORLD);
			
			//Kathe diergasia briskei to plithos twn miden 
			plithosMiden=0;
			for(i=0;i<9;i++){
				if(loc_matrix[i] == 0) plithosMiden++; 	
				else tmp = loc_matrix[i];
			}
			if(plithosMiden == 8) item = tmp;
			else item = 0;
			
			// O pinakas itemArray periexei tis times pou prepei na 
			// afairethoun apo tis 9 diergasies
			root=0;
			MPI_Gather(&item, 1, MPI_INT, itemArray, 1, MPI_INT, root, MPI_COMM_WORLD);
			
			// H diergasia 0 afou exei mazepsei ton itemArray 
			// ton stelnei pisw stis diergasies
			root=0;
			MPI_Bcast(&itemArray, 9, MPI_INT, root, MPI_COMM_WORLD);	
			
			// Ta stoixeia tou itemArray diagrafontai apo tis diergasies
			for(i=0;i<9;i++){
				if(itemArray[i]!=0){
					for(j=0;j<9;j++){
						if (loc_matrix[j] == itemArray[i] && myrank != i){
							loc_matrix[j] = 0;
						}
					} 
				}
			}
			// Ksanamazeuei tis times apo tis diergasies 
			// auth ti fora me perissotera midenika
			root=0;
			MPI_Gather(loc_matrix, 9, MPI_INT, a, 9, MPI_INT, root, MPI_COMM_WORLD);
			
			// Telos ta pernaei ston arxiko pinaka sudoku 
			if(myrank == 0){
				counter=0;
				for(j=0;j<9;j++){
					for(k=0;k<9;k++){
						sudoku[grammi][j][k] = a[counter] ;
						counter++;
					}
				}
			}	
		}
		// ~ Telos afaireshs arithmwn ana grammh
		
		/* O kwdikas pou akolouthei einai copy - paste me ton proigoumeno
		 * Diladh oti kanw gia tis grammes tou pinaka kanw kai gia tis stiles 
		 * kai gia ta plaisia tou sudoku.
		 * To mono pou allazei einai oi diastaseis 
		*/
		
		//	Meta tha afairesei tous arithmous ana stili
		for(stili=0;stili<9;stili++){
			
			if(myrank==0){
				counter=0;
				for(i=0;i<9;i++){
					for(k=0;k<9;k++){
						a[counter] = sudoku[i][stili][k];
						counter++;
					}
				}
			}
			root=0;
			MPI_Scatter(a, 9, MPI_INT, loc_matrix, 9, MPI_INT, root, MPI_COMM_WORLD);
			
			plithosMiden=0;
			for(i=0;i<9;i++){
				if(loc_matrix[i] == 0) plithosMiden++; 	
				else tmp = loc_matrix[i];
			}
			if(plithosMiden == 8) item = tmp;
			else item = 0;
			
			root=0;
			MPI_Gather(&item, 1, MPI_INT, itemArray, 1, MPI_INT, root, MPI_COMM_WORLD);
			
			
			root=0;
			MPI_Bcast(&itemArray, 9, MPI_INT, root, MPI_COMM_WORLD);	
			
			for(i=0;i<9;i++){
				if(itemArray[i]!=0){
					for(j=0;j<9;j++){
						if (loc_matrix[j] == itemArray[i] && myrank != i){
							loc_matrix[j] = 0;
						}
					} 
				}
			}
			
			root=0;
			MPI_Gather(loc_matrix, 9, MPI_INT, a, 9, MPI_INT, root, MPI_COMM_WORLD);
			
			if(myrank == 0){
				counter=0;
				for(j=0;j<9;j++){
					for(k=0;k<9;k++){
						sudoku[j][stili][k] = a[counter] ;
						counter++;
					}
				}
			}	
		}
		// ~ Telos afaireshs arithmwn ana stili
		
		
		//  Afairesh arithmwn ana plaisio
		for(grammi=0;grammi<7;grammi=grammi+3){
			for(stili = 0;stili<7;stili=stili+3){
			
				if(myrank==0){
					counter=0;
					for(i=grammi;i<grammi+3;i++){
						for(j=stili;j<stili+3;j++){
							for(k=0;k<9;k++){
								a[counter] = sudoku[i][j][k];
								counter++;
							}
						}
					}
				}
				root=0;
				MPI_Scatter(a, 9, MPI_INT, loc_matrix, 9, MPI_INT, root, MPI_COMM_WORLD);
				
				plithosMiden=0;
				for(i=0;i<9;i++){
					if(loc_matrix[i] == 0) plithosMiden++; 	
					else tmp = loc_matrix[i];
				}
				if(plithosMiden == 8) item = tmp;
				else item = 0;
				
				root=0;
				MPI_Gather(&item, 1, MPI_INT, itemArray, 1, MPI_INT, root, MPI_COMM_WORLD);
				
				
				root=0;
				MPI_Bcast(&itemArray, 9, MPI_INT, root, MPI_COMM_WORLD);	
				
				for(i=0;i<9;i++){
					if(itemArray[i]!=0){
						for(j=0;j<9;j++){
							if (loc_matrix[j] == itemArray[i] && myrank != i){
								loc_matrix[j] = 0;
							}
						} 
					}
				}
				root=0;
				MPI_Gather(loc_matrix, 9, MPI_INT, a, 9, MPI_INT, root, MPI_COMM_WORLD);
				if(myrank == 0){
					counter=0;
					for(i=grammi;i<grammi+3;i++){
						for(j=stili;j<stili+3;j++){
							for(k=0;k<9;k++){
								sudoku[i][j][k] = a[counter] ;
								counter++;
							}
						}
					}
				}	
			}
		}
		// ~ Afairesh arithmwn ana plaisio
	}
	
	// Ektipwsh limenou Sudoku meta apo 4 prospatheies scanarismatos tou pinaka
	if(myrank==0){
		printf("\nSUDOKU SOLVED :\n");
		for(i=0;i<9;i++){
			printf("|");
			for(j=0;j<9;j++){
				for(k=0;k<9;k++){
					if(sudoku[i][j][k]!=0) printf("%d\t",sudoku[i][j][k]);
				}
			}
			printf("|\n");
		}
	}
	MPI_Finalize();
    return 0;
}
