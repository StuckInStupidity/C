#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int open_close(const char *filename){
	if(filename){
		FILE *file = fopen(filename,"r");
		if(!file) return 1;
		else {fclose(file); return 0;}
	}
	return 1;
}

int read_n_bytes(const char *filename, size_t n){
	if(filename){
	FILE *file = fopen(filename,"r");
	if(!file) return 1;
	char *f = malloc(n+1);
	if(!f) return 1;
	size_t m = fread(f, sizeof(char), n, file);
	f[m] = '\0';
	printf("%s\n",f);
	free(f);
	fclose(file);
	return 0;
	}
	return 1;
}
int read_bytes(const char *filename){
	if(filename){
	FILE *file = fopen(filename,"r");
	if(!file) return 1;
	char c;
	while((c = fgetc(file))!=EOF) printf("%c",c);
	printf("\n");
	fclose(file);
	return 0;
	}
	return 1;
}

int write_one_by_one(char *filename, const char *text){
	if(filename){
		FILE *file = fopen(filename, "w+");
		if(!file) return 1;
		fputs(text, file);
		fclose(file);
		return 0;
	}
	return 1;
}

int write_all_in_one(char *filename, const char *text){
if(filename){
	FILE *file = fopen(filename, "w+");
	if(!file) return 1;
	fputs(text, file);
	fclose(file);
	return 0;
}
return 1;
}

int count(const char *filename){
	if(filename){
		FILE *file = fopen(filename, "r");
		if(!file) return 1;
		size_t c = 0, w = 0, l = 0; char s;
		while((s = fgetc(file))!=EOF) {c++;if(s=='\n' || s=='\t' || s==' ') {if(s=='\n') l++; w++;}}
		printf("> characters: %d\n> words: %d\n> lines: %d\n", c, w, l);
		fclose(file);return 0;	
	}
	return 1;
}

int filter(char* filename){
	if(filename){
		FILE *file = fopen(filename, "r");
		if(file){
		char *line = NULL;
		size_t len = 0;
		size_t read;
		while((read = getline(&line, &len, file))!=-1){
			int s=0; 
			for(int i = 0; i < read; i++){
				int n = line[i]-'\0'; if(n>=0 && n<=9){
					if(i%2==0) s+=n%10;
					else {int nn=(n%10)*2; if(n<=9) s+=nn; else s+=(nn%10+nn/10);}
				}
			}
			if(s%10==0) printf("%s", line);
		}
		if(line) free(line);
		fclose(file);
		return 0;
		}
		return 1;
	}
	return 1;
}

int hidden_message(const char *filename, const char delim){
	if(!filename) return 1;
	FILE *file = fopen(filename, "r");
	if(!file) return 1;
	char *line = NULL; size_t len = 0; size_t read;
	while((read = getdelim(&line, &len, delim, file))!=-1){
		putchar(line[0]);
	}
	if(line) free(line);
	fclose(file);
	return 0;
}

int my_cp(const char *src, const char *dest){
	if(src && dest){
		FILE *file = fopen(src, "r");	
		if(!file) return 1;
		FILE *f = fopen(dest, "w");
		if(!f) return 1;
		char *buf = malloc(SIZE); size_t m;
		while(0 < (m = fread(buf, sizeof(char), SIZE, file))) fwrite(buf, 1, m, f);
		free(buf);fclose(file);fclose(f);
		return 0;
	}
	return 1;
}

int my_grep(char *filename, char *expr){
	if(filename && expr){
		FILE *file = fopen(filename, "r");
		if(!file) return 2;
		char *line = NULL;
		size_t len = 0;
		size_t read;
		char *sub = NULL;
		int ok = 0;
		while((read = getline(&line, &len, file))!=-1){
			sub = strstr(line, expr);
			if(sub) {printf("%s", line);ok=1;}
		}
		if(line) free(line); fclose(file);
		if(ok) return 1;
		else return 0;
	}
	return 2;
}

int find_max_val(char *filename){
	if(!filename) return 1;
	FILE *file = fopen(filename, "r");
	if(!file) return 1;
	char *line = NULL; size_t len = 0; size_t read; int max=0; char *s = NULL; int cnt=0, c=0; int ok=0;
	while((read=getline(&line, &len, file))!=-1){
		int id; ok=0; read--; while(line[read]=='\n' || line[read]=='\t') read--;
		for(int i = 0; i <= read; i++) if(line[i]==':') {ok++; id = i; line[id]='\0';}
		if(ok!=1 || line[0]=='\0' || line[read]=='\0' || (line[id+1]!='-' && !(line[id+1]>47 && line[id+1]<58))) {if(line) free(line);if(s) free(s);fclose(file);return 2;}
		int var = atoi(line+id+1); if(var>max) {max = var; if(s) free(s); s = strdup(line);}
		cnt+=var;c++;
	}
	if(ok && s){
		printf("%s\n%d\n%d",s,max,cnt/c);
		if(line) free(line); if(s) free(s);
		fclose(file);
		return 0;
	}
	else {if(line) free(line);if(s) free(s);fclose(file);return 2;}
}

int print_lines(const char *filename){
	if(filename){
		FILE *file = fopen(filename, "r");
		if(file){
			char *line = NULL;
			size_t len = 0;
			size_t read;
			while((read = getline(&line, &len, file))!=-1) printf("> %s", line);
			if(line) free(line);
			fclose(file);
		}
	}
}

enum data_type {
    STRING,
    INTEGER,
    POINTER
};

int write_format(void *data, enum data_type type, char *filename)
{
    if(data && filename){
    FILE *file = fopen(filename, "a");
    if(!file) return 1;
    if(type==STRING) {char *s = (char *)data; fprintf(file, "String: %s\n", s);}
    else if(type==INTEGER) {int *var = (int *)data; fprintf(file, "Integer: %d\n", *var);}
    else if(type==POINTER) {fprintf(file, "Pointer: %p\n", data);}
    fclose(file);
    return 0;
    }
    return 1;
}

int main(){ //common streams test
	char *line = NULL; size_t len = 0; size_t read;
	while((read = getline(&line, &len, stdin))!=-1){
		int i=0, cnt=0, ok = 1;
		read--;while(line[read]=='\n' || line[read]=='\t') read--;
		if(line[0]=='.' || line[read]=='.') {fprintf(stderr, "Error: %s", line); fflush(stderr);}
		else{
			while(i<=read && ok){
				if(line[i]=='.') cnt++;
				else if(!((line[i]>=65 && line[i]<=90) || (line[i]>=97 && line[i]<=122) || (line[i]>=48 && line[i]<=57))) ok = 0;
				i++;
			}
			if(cnt!=1 || !ok) {fprintf(stderr, "Error: %s", line); fflush(stderr);}
			else {fprintf(stdout, "Accepted: %s", line); fflush(stdout);}
		}
	}
	if(line) free(line);
}
