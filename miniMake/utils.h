#ifndef UTILS_H
#define UTILS_H

struct list {
	struct var *first_var;
	struct rule *first_rule;
	struct wanted *first_wanted;
};

struct var {
	char *name;
	char *value;
	struct var *next;
};

struct rule {
	char *name;
	char **dep;
	int nb_dep;
	char **rec;
	int nb_rec;
	struct rule *next;
};

struct wanted {
	char *name;
	struct wanted *next;
};

int helpy();
int error_display(char *name);
void clear_wanted(struct list *lst);
void clear_var(struct list *lst);
void clear_rule(struct list *lst);
char *normalize(char *s);
char *trim(char *s);
char *expand(char *s, struct list *lst);
char *find_var(struct list *lst, char *name);
int parse(FILE *file, struct list *lst);
void pretty_print(struct list *lst);
struct rule *find_rule(struct list *lst, char *name);
int fork_bomb(struct list *lst, struct rule *tmp);

#endif