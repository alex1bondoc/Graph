#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct pair {
	int u, v, cost;
} Pair;

typedef Pair V;

typedef struct list {
	V data;
	struct list *prev, *next;
}*List;

int contains(List list, V data){
	List p;
	while(p){
		if((list->data.u==data.v||list->data.u==data.u)&&(list->data.v==data.u||list->data.v==data.v))
			return 1;
		p = p->next;
	}
	return 0;
}

List initList(V data)
{
	List list;

	list = (List) malloc(sizeof(struct list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return list;
}

List addFirst(List list, V data)
{
	List new;

	if (list == NULL)
		return initList(data);
	new = initList(data);
	new->next = list;
	list->prev = new;
	return new;
}

List addLast(List list, V data)
{
	List new, tmp;

	if (list == NULL)
		return initList(data);
	new = initList(data);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return list;
}

List deleteItem(List l, V data) {
	if(l == NULL) {
		return NULL;
	} else {
		List tmp = l, prev;
		if(tmp->data.v == data.v) {
			l = l->next;
			free(tmp);
			if (l)
				l->prev = NULL;
			return l;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
		while(tmp != NULL) {
			if(tmp->data.v == data.v) {
				prev->next = tmp->next;
				if (tmp->next != NULL)
					tmp->next->prev = prev;
				free(tmp);
				return l;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		return l;
	}
}

List freeList(List list)
{
	List tmp;

	if (list == NULL)
		return list;
	while (list != NULL) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return NULL;
}