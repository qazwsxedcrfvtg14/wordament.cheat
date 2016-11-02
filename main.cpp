#include<bits/stdc++.h>
#include<windows.h>
#define f first
#define s second
using namespace std;

struct node{
	int ok;
	node* to[26];
	//node(bool x){ok=x;}
	node(){
		ok=0;
		for(int i=0;i<26;i++)to[i]=NULL;
		}
	}root;
string ar[10][10];
int mp[10][10];
bool chk(int x,int y){
	if(x<0||y<0||x>3||y>3)return 0;
	return 1;
	}
int dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1};
int dtime=300,mtime=40,maxlim=100,cheat=0,nodel=0,bas=6;
map<string,bool>ma;
bool stop;
void smov(int x,int y){
	//x+=rand()%3;
	//y+=rand()%3;
	POINT pt;
	GetCursorPos(&pt);
	Sleep(1);
	//mouse_event(0, 0, 0, 0, 0 );
	//SetCursorPos(pt.x+(x-pt.x)+rand()%2-1,pt.y+(y-pt.y)+rand()%2-1);

	for(int i=1;i<=mtime;i++){
		Sleep(1);
		mouse_event(0, 0, 0, 0, 0 );
		SetCursorPos(pt.x+(x-pt.x)*i/mtime,pt.y+(y-pt.y)*i/mtime);
		}
	}
bool chkcol(int x,int y){
	HDC hdc_ = GetDC(GetDesktopWindow()) ;
	//COLORREF color = GetPixel(hdc_,300,350);
	//POINT pt;
	//GetCursorPos(&pt);
	//x=pt.x;y=pt.y;
	COLORREF color = GetPixel(hdc_,x*1.5,y*1.5);
	int _red = GetRValue(color);
	int _green = GetGValue(color);
	int _blue = GetBValue(color);
	//if(x!=600||y!=240)
		//printf("X:%3d Y:%3d R:%3d G:%3d B:%3d\n",x,y,_red,_green,_blue);
	//Sleep(500);
	if(x==600&&y==240)
		if(_red==240&&_green==150)stop=1;
	return _red>=200&&_green<150&&_blue<80;
	}
void mov(int x,int y){
	x+=rand()%3;
	y+=rand()%3;
	POINT pt;
	GetCursorPos(&pt);
	smov(pt.x+(x-pt.x),pt.y+(y-pt.y));
	}
void F(int x,int y,int l,node *rot,string s){
	if(stop)return;
	if(mp[x][y])return;
	int len=ar[x][y].length(),ed=0;
	for(int j=0;j<len;j++){
		if(ar[x][y][j]=='-'&&j==0){
			ed=1;
			continue;
			}
		if(ar[x][y][j]=='-'&&j==len-1){
			if(s!="")return;
			continue;
			}
		if(rot->to[ar[x][y][j]-'A']!=NULL)
			rot=rot->to[ar[x][y][j]-'A'],s+=ar[x][y][j]-'A';
		else
			return;
			}
	mp[x][y]=l;
	if(rot->ok&&!ma[s]&&(s.length()>=bas||s.length()!=l)&&s.length()<=maxlim){
		while(chkcol(600,240));
		ma[s]=1;
		//cout<<s<<endl;
		int sx,sy;
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				if(mp[i][j]==1)
					sx=i,sy=j,mov(85+77*j,120+77*i);

		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
		for(int k=2;k<=l;k++){
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
					if(mp[i][j]==k)
						mov(85+77*j,120+77*i);
			}
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		//mov(85+77*sy,120+77*sx-25);
		Sleep(dtime);
		//cout<<85+77*sy<<","<<120+77*sx-25<<endl;
		if(chkcol(85+77*sy,120+77*sx-25)){
			cout<<"error :"<<s<<endl;
			if(!nodel){
				int len=s.length();
				for(int i=0;i<len;i++)
					if(s[i]>='a'&&s[i]<='z')
						s[i]=s[i]-'a'+'A';
				node *now=&root;
				for(int i=0;i<len;i++){
					if(now->to[s[i]-'A']==NULL){
						//puts("None");
						now=NULL;
						break;
						}
					now=now->to[s[i]-'A'];
					}
				if(now!=NULL){
					if(now->ok)
						now->ok=0;
					}
				}

			}
		/*for(int i=0;i<4;i++,puts(""))
			for(int j=0;j<4;j++)
				if(mp[i][j])
					printf("%2d ",mp[i][j]);
				else
					printf(" . ");
		puts("");*/
		}
	if(!ed)
		for(int i=0;i<8;i++)
			if(chk(x+dx[i],y+dy[i]))
					F(x+dx[i],y+dy[i],l+1,rot,s);
	mp[x][y]=0;
	}
fstream fout;
int cou;
void Out(node *rot,string s){
	if(rot->ok){
		fout<<s<<endl;
		cou++;
		}
	for(int i=0;i<26;i++)
		if(rot->to[i]!=NULL)
			Out(rot->to[i],s+(char)(i+'A'));
	}
int main(){
	//POINT pt;
	//GetCursorPos(&pt);
	//SetCursorPos(85+80*0,120+80*0);
	//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
	/*while(1){
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				chkcol(85+77*j,120+77*i+5);//,mov(85+77*j,120+77*i+5),Sleep(200);
		//puts("");
		}*/
	string s;
	fstream fin;
    fin.open("Words.txt",ios::in);
    int cnt=0;
	while(fin>>s){
		cnt++;
		int len=s.length();
		for(int i=0;i<len;i++)
			if(s[i]>='a'&&s[i]<='z')
				s[i]=s[i]-'a'+'A';
		node *now=&root;
		for(int i=0;i<len;i++){
			if(now->to[s[i]-'A']==NULL)
				now->to[s[i]-'A']=new node;
			now=now->to[s[i]-'A'];
			}
		now->ok=1;
		}
	fin.close();
	printf("include: %d words\n",cnt);
	while(cin>>s){
		int len=s.length();
		for(int i=0;i<len;i++)
			if(s[i]>='a'&&s[i]<='z')
				s[i]=s[i]-'a'+'A';
		if(s=="ASK"){
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++){
					cin>>ar[i][j];
					int alen=ar[i][j].length();
					for(int k=0;k<alen;k++)
						if(ar[i][j][k]>='a'&&ar[i][j][k]<='z')
							ar[i][j][k]=ar[i][j][k]-'a'+'A';

					}
			system("cls");

			stop=0;
			for(int k=0;k<=cheat;k++){
				ma.clear();
				for(int i=0;i<4;i++)
					for(int j=0;j<4;j++)
						F(i,j,1,&root,"");
				}
			}
		else if(s=="CHEAT"){
			//cin>>dtime;
			//cin>>mtime;
			dtime=20;
			mtime=7;
			maxlim=100;
			cheat=1;
			nodel=1;
			}
		else if(s=="NOCHEAT"){
			//cin>>dtime;
			//cin>>mtime;
			dtime=300;
			mtime=40;
			maxlim=100;
			cheat=0;
			nodel=0;
			}
		else if(s=="BASE"){
			cin>>bas;
			}
		else if(s=="CHK"){
			cin>>s;
			len=s.length();
			for(int i=0;i<len;i++)
				if(s[i]>='a'&&s[i]<='z')
					s[i]=s[i]-'a'+'A';
			node *now=&root;
			for(int i=0;i<len;i++){
				if(now->to[s[i]-'A']==NULL){
					puts("No");
					now=NULL;
					break;
					}
				now=now->to[s[i]-'A'];
				}
			if(now!=NULL){
				if(now->ok)
					puts("Yes");
				else
					puts("No");
				}
			}
		else if(s=="SAVE"){
			cou=0;
			fout.open("Words.txt",ios::out);
			Out(&root,"");
			printf("Save: %d Words\n",cou);
			fout.close();
			}
		else if(s=="EXIT"){
			fout.open("Words.txt",ios::out);
			Out(&root,"");
			fout.close();
			return 0;
			}
		else if(s=="DELOFF"){
			nodel=1;
			}
		else if(s=="DELON"){
			nodel=0;
			}
		else if(s=="DEL"){
			cin>>s;
			len=s.length();
			for(int i=0;i<len;i++)
				if(s[i]>='a'&&s[i]<='z')
					s[i]=s[i]-'a'+'A';
			node *now=&root;
			for(int i=0;i<len;i++){
				if(now->to[s[i]-'A']==NULL){
					puts("None");
					now=NULL;
					break;
					}
				now=now->to[s[i]-'A'];
				}
			if(now!=NULL){
				if(now->ok)
					now->ok=0,puts("Ok~");
				else
					puts("None");
				}
			}
		else{
			node *now=&root;
			for(int i=0;i<len;i++){
				if(now->to[s[i]-'A']==NULL)
					now->to[s[i]-'A']=new node;
				now=now->to[s[i]-'A'];
				}
			now->ok=1;
			}
		}
	return 0;
    }
