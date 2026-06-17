/* NOT CHECKING SYNTAX ERRORS*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "utils.h"

int helpy(){
	printf("Usage: minimake [OPTIONS] [TARGETS]\n");
	printf("    OPTIONS can be:\n");
	printf("        \"-h\"            to display the helper\n");
	printf("        \"-p\"            to print the rules and variables\n");
	printf("        \"-f\" <filename> to change the make config file, \"Makefile\" by default\n");
	printf("    TARGETS are target name of makefile rule to execute\n");
	return 0;
}

int error_display(char *name){
	printf("minimake: *** [%s]\n", name);
	return 2;
}

void clear_wanted(struct list *lst){
	struct wanted *head = lst->first_wanted;
	while(head) {
		struct wanted *tmp = head->next;
		free(head);
		head = tmp;
	}
}

void clear_rule(struct list *lst){
	struct rule *head = lst->first_rule;
	while(head) {
		struct rule *tmp = head->next;
		for(int i = 0; i < head->nb_rec; i++) free(head->rec[i]);
		for(int i = 0; i < head->nb_dep; i++) free(head->dep[i]);
		free(head->name); free(head->dep); free(head->rec); free(head);
		head = tmp;
	}
}

void clear_var(struct list *lst){
	struct var *head = lst->first_var;
	while(head) {
		struct var *tmp = head->next;
		free(head->name); free(head->value); free(head);
		head = tmp;
	}
}

char *normalize(char *s){
	//s is a copy of pointer line and since i dont dereference with equal like linked lists i wont loose original cursor to free line
	while(*s == ' ' || *s == '\t') s++;
	char *f = s+strlen(s)-1;
	while(f > s && (*f == ' ' || *f == '\t')) f--;
	*(f+1) = '\0';
	return s;
}

char *trim(char *s){
	while(*s == ' ' || *s == '\t') s++;
	return s;
}

char *expand(char *s, struct list *lst){
	size_t len = 0; char *ans = malloc(1); ans[0]='\0'; size_t size = strlen(s);
	for(size_t i = 0; i < size; i++){
		if(s[i]=='$' && s[i+1]=='{'){
			i+=2; int j=0; size_t ii = i;
			while(s[i] && s[i]!='}') {j++; i++;}
			char *val = malloc(j+1);
			strncpy(val, s + ii, j);
			*(val+j) = '\0';
			char *exp = find_var(lst,val); free(val);
			if(exp==NULL) exp="";
			ans = realloc(ans, len + strlen(exp) + 1);
			strcpy(ans + len, exp); len += strlen(exp);
		}
		else{
			ans = realloc(ans, len+2);
			ans[len]=s[i]; len++; ans[len]='\0';
		}
	}
	return ans;
}

char *find_var(struct list *lst, char *name){
	struct var *tmp = lst->first_var;
	while(tmp){
		if(strcmp(tmp->name, name)==0) return tmp->value;
		tmp = tmp->next;
	}
	return NULL;
}

int parse(FILE *file, struct list *lst){
	char *line = NULL;
	size_t len = 0;
	int in_rule = 0;
	struct var *cur_var = NULL;
	struct rule *cur_rule = NULL;
	ssize_t read;
	while ((read = getline(&line, &len, file)) != -1){
		while(read>0 && (line[read - 1] == '\n' || line[read - 1] == '\r')) {read--; line[read]='\0';}
		if(line[0]=='\t'){
			if(!in_rule){
				clear_wanted(lst); clear_rule(lst); clear_var(lst); free(line);
				return error_display("command outside of rule");
			}
			cur_rule->rec = realloc(cur_rule->rec, sizeof(char *) * (cur_rule->nb_rec + 1));
			char *p = trim(line);
			*(cur_rule->rec + cur_rule->nb_rec) = strdup(p);
			(cur_rule->nb_rec)++;
			continue;
		}

		char *found = strchr(line, '#'); if(found) *found='\0';

		found = strchr(line, '=');
		if(found){
			in_rule = 0;
			*found = '\0';
			char *rw = strdup(line); char *nn = normalize(rw);
			char *name = expand(nn, lst); free(rw);
			if(strcmp(name, "")==0) {free(name); continue;}
			char *rv = strdup(found+1); char *nv = trim(rv);
			char *value = expand(nv, lst); free(rv);
			struct var *v = malloc(sizeof(struct var)); 
			v->name = name; v->value = value; v->next = NULL;
			if(lst->first_var==NULL) lst->first_var = v;
			else cur_var->next = v; 
			cur_var = v;
			continue;
		}
		found = strchr(line, ':');
		if(found){
			in_rule = 1; *found = '\0';
			char *rr = strdup(line); char *nr = normalize(rr);
			char *name = expand(nr, lst); free(rr);
			char *rd = strdup(found+1); char *nd = trim(rd);
			char *dep_l = expand(nd, lst); free(rd);
			struct rule *r = malloc(sizeof(struct rule));
			r->name = name; r->nb_dep = 0; r->nb_rec = 0; r->dep = NULL; r->rec = NULL; r->next = NULL;
			char *word = dep_l; 
			while(*word != '\0'){ 
				// strtok ??
				while(*word == ' ' || *word == '\t') word++;
				if(*word=='\0') break;
				char *ptr = word;
				while(*word != ' ' && *word != '\t') word++;
				int n = word - ptr;
				char *d = malloc(n+1); memcpy(d, ptr, n); d[n]='\0';
				r->dep = realloc(r->dep, sizeof(char *) * (r->nb_dep + 1));
				*(r->dep + r->nb_dep) = d; (r->nb_dep)++;
			}
			free(dep_l);
			if(lst->first_rule==NULL) lst->first_rule = r;
			else cur_rule->next = r; 
			cur_rule = r;
		}
		//other cases => not useful lines
	}
	free(line);
	return 0;
}

void pretty_print(struct list *lst){
	printf("# variables\n");
	struct var *tmp = lst->first_var;
	while(tmp){
		printf("'%s' = '%s'\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	printf("\n# rules\n");
	struct rule *pmt = lst->first_rule;
	while(pmt){
		if(strcmp(pmt->name, "")!=0){
			printf("(%s):", pmt->name);
			for(int i = 0; i < pmt->nb_dep; i++) printf(" [%s]", pmt->dep[i]);
			printf("\n");
			for(int i = 0; i < pmt->nb_rec; i++) printf("\t'%s'\n", pmt->rec[i]);
		}
		pmt = pmt->next;
	}
}

struct rule *find_rule(struct list *lst, char *name){
	struct rule *tmp = lst->first_rule;
	while(tmp){
		if(strcmp(tmp->name, name)==0) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

int fork_bomb(struct list *lst, struct rule *tmp){
	for(int i = 0; i < tmp->nb_dep; i++){
		struct rule *need = find_rule(lst, (tmp->dep)[i]);
		if(!need) {printf("minimake: *** No rule to make target '%s', needed by '%s'.  Stop.\n", (tmp->dep)[i], tmp->name); return 2;}
		if(fork_bomb(lst, need)==2) return 2;
	}
	for(int j = 0; j < tmp->nb_rec; j++){
		char *real = expand(tmp->rec[j], lst);
		printf("%s\n", real); fflush(stdout);
		pid_t pid = fork();
		if(pid==0){
			char *exea[] = {"/bin/sh", "-c", real, NULL};
			execvp("/bin/sh", exea);
			exit(255);
		} else if(pid > 0){
			int status; waitpid(pid, &status, 0); //wait forked child
			free(real);
			if(!WIFEXITED(status) || WEXITSTATUS(status)!=0) {printf("minimake: *** [%s] Error 1\n", tmp->name); return 0;}
		}
	}
	return 0; //add something to detect forced return in fork commands to return 2 at the very end instead of zero
}

int main(int argc, char *argv[]){

	int f = 0, p = 0, h = 0;
	char *filename = NULL;
	
	struct list l; l.first_var = NULL; l.first_rule = NULL; l.first_wanted = NULL;
	struct wanted *tail = NULL;

	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "-p")==0) p = 1;
		else if(strcmp(argv[i], "-f")==0) {
			if(i==argc-1) {
				clear_wanted(&l); clear_rule(&l); clear_var(&l);
				return error_display("no given file");
			}
			else {f = 1; i++; filename = argv[i];}
		}
		else if(strcmp(argv[i], "-h")==0) h = 1;
		else{
			struct wanted *w = malloc(sizeof(struct wanted)); 
			w->next = NULL; w->name = argv[i];
			if(l.first_wanted==NULL) l.first_wanted = w;
			else tail->next = w;
			tail = w;
		}
	}
	
	if(h) {
		clear_wanted(&l); clear_rule(&l); clear_var(&l);
		return helpy();
	}

	FILE *file = NULL;
	if(f) file = fopen(filename, "r");
	else file = fopen("Makefile", "r");
	if(!file) {
		clear_wanted(&l); clear_rule(&l); clear_var(&l);
		error_display("not accessible file"); return 3;
	}
	
	if(parse(file, &l)==2) {fclose(file); return 2;}

	if(p) {
		pretty_print(&l);
		clear_wanted(&l); clear_rule(&l); clear_var(&l);
		fclose(file);
		return 0;	
	}

	if(l.first_rule==NULL) {
		clear_wanted(&l); clear_rule(&l); clear_var(&l);
		fclose(file);
		printf("minimake: *** No targets.  Stop.\n"); return 2;
	}
	
	if(l.first_wanted==NULL) {
		if(fork_bomb(&l, l.first_rule)==2) {
			clear_wanted(&l); clear_rule(&l); clear_var(&l);
			fclose(file);
			return 2;
		}
	}

	int ok = 0;

	tail = l.first_wanted;
	while(tail){
		struct rule *f = find_rule(&l, tail->name);
		if(f==NULL) {printf("minimake: *** No rule to make target '%s'.  Stop.\n", tail->name); ok = 2;}
		else {
			if(fork_bomb(&l, f)==2) {
				clear_wanted(&l); clear_rule(&l); clear_var(&l);
				fclose(file);
				return 2;
			}
		}
		tail = tail->next;
	}
	
	clear_wanted(&l); clear_rule(&l); clear_var(&l);
	fclose(file);
	return ok;
}
