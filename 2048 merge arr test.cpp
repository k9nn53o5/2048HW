#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip> 

using namespace std;

void mergearr(int *);
void dirmergearr(int arr[][4],char);
void keypress(int arr[][4],char);
int endjudge(int arr[][4]);
int main(){
	int arr[4] = {2,2,2,2};
	int arr2D[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
//	char dir = 'S';
	
	
/*	mergearr(arr);
	for(int i=0;i<4;i++){	
		cout << arr[i];
	}	
*/	

	/*
	dirmergearr(arr2D,dir);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<arr2D[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	int i=0;
	while( i <2){
		srand(time(NULL));
		int r1=rand()%4;
		int r2=rand()%4;
		if(arr2D[r1][r2] == 0){
			arr2D[r1][r2] = 2;
			i++;
		}
	}
	char d='\0';
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<setfill(' ')<<setw(4)<<arr2D[i][j]<<" ";
		}
		cout<<endl;
	}
	system("CLS");
	while(d != 'c'){
		scanf("%c",&d);
		keypress(arr2D,d);
		system("CLS");
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				cout<<setfill(' ')<<setw(4)<<arr2D[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	return 0;
} 

void dirmergearr(int arr[][4],char dir){
	int mergetemp[4]={0};
	if(dir == 'w'){
		for(int j=0;j<4;j++){
			for(int i1=0;i1<4;i1++){
				mergetemp[i1]=arr[i1][j];
			}
			mergearr(mergetemp);
			for(int i2=0;i2<4;i2++){
				arr[i2][j]=mergetemp[i2];
			}
		}
	}
	else if(dir == 's'){
		for(int j=0;j<4;j++){
			for(int i1=0;i1<4;i1++){
				mergetemp[i1]=arr[3-i1][j];
			}
			mergearr(mergetemp);
			for(int i2=0;i2<4;i2++){
				arr[3-i2][j]=mergetemp[i2];
			}
		}
	}
	else if(dir == 'a'){
		for(int j=0;j<4;j++){
			for(int i1=0;i1<4;i1++){
				mergetemp[i1]=arr[j][i1];
			}
			mergearr(mergetemp);
			for(int i2=0;i2<4;i2++){
				arr[j][i2]=mergetemp[i2];
			}
		}
	}
	else if(dir == 'd'){
		for(int j=0;j<4;j++){
			for(int i1=0;i1<4;i1++){
				mergetemp[i1]=arr[j][3-i1];
			}
			mergearr(mergetemp);
			for(int i2=0;i2<4;i2++){
				arr[j][3-i2]=mergetemp[i2];
			}
		}
	}
	else{
		cout<<"check Ur dir input\n";
		cout<<dir;
	}
}

void mergearr(int arr[]){
	int temp[4]={0};
	int newarr[4]={0};
	int tempnum=0;
	int newarrnum=0;
	int i=0;
	do{
		temp[tempnum] = arr[i];

		if(arr[i] > 0){
			tempnum++;
		}
		if(tempnum == 2){
			if(temp[0] == temp[1]){
				newarr[newarrnum]= temp[0]*2;
				newarrnum++;
				temp[0]=0;
				temp[1]=0;
				tempnum=0;
				}
			else if(temp[0] != temp[1]){
				newarr[newarrnum]=temp[0];
				newarrnum++;
				temp[0]=temp[1];
				temp[1]=0;
				tempnum--;				
			}
		}
		i++;
	}while(i<4);
	newarr[newarrnum]=temp[0];
	cout<<endl;
	for(int j=0;j<4;j++){
		arr[j]=newarr[j];
	}
}

void keypress(int arr[][4],char dir){
	if(dir == 'a' || dir == 'd' ||dir == 's' ||dir == 'w' ){
		dirmergearr(arr,dir);
		int judge = endjudge(arr);
		if(judge == 0){
			int xrand,yrand;
			srand(time(NULL));
			while(1){
				xrand = rand()%4;
				yrand = rand()%4;
				if(arr[xrand][yrand] == 0){
					int rand0_9;
					rand0_9 = rand()%10;
					if(rand0_9<9){
						arr[xrand][yrand]=2;
					}
					else if(rand0_9==9){
						arr[xrand][yrand]=4;
					}
					break;
				}
			}
		}
		else if(judge == -1){
		}	
		else if(judge == 1){
			cout<<endl<<"U win !!!!!";
		}
		else if(judge == 2){
			cout<<endl<<"U lose !!!!!";
			system("Pause");
		}
	}
}

int endjudge(int arr[][4]){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(arr[i][j] == 0){
					return 0;
				}
			}
		}
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(arr[i][j] == 2048){
					return 1;
				}
			}
		}	
		
		for(int i=0;i<4;i++){
			for(int j=0;j<3;j++){
				if(arr[i][j] == arr[i][j+1]){
					return -1;
				}
				if(arr[j][i] == arr[j+1][i]){
					return -1;
				}
			}
		}
	
		return 2;
		
}
