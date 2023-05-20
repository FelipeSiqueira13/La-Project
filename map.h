#ifndef ___MAP_H___
#define ___MAP_H___

typedef struct map{
	char obj[500][500];	//id do objeto?
	int dist[500][500];
	int vision[500][500]; //0 = nao visto, 1 = visto mas n agr, 2 = esta vendo agr
	int isenemyhere[500][500];
}MAP;

#endif