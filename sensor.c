#include "doubleLinkedList.h"
#include "pthread.h"
#include <sys/types.h>

int numSensors, temp;
doubleLL temperature_List = makeDLL();
node myNode;

pthread_cond_t self;//do we need this?
pthread_mutex_t locker;

typedef struct {
	int id;
	int seed; //for srand
}sensor_struct;

void sensor(sensor_struct * data);
void canIAdd(int id);
void addTemp(int id);

int main(int argc, char *argv[]){
	int i, maxSensors;
	sensor_struct *data;
	pthread_t sensors[25];
	int sTime;
	long lTime;

	if(argc != 2){
		puts("ERROR! Format should be: ./sensor #ofSensors\n");
		exit(0);
	}

	numSensors = atoi(argv[1]); //to run --> ./nameofMain #sensors
	printf("You want %d sensors\n", numSensors);

	pthread_mutex_init(&locker, NULL);

	pthread_cond_init(&self, NULL);

	for(i=0; i<numSensors; i++){
		data = (sensor_struct*)malloc(sizeof(sensor_struct));
		data->id = i;
		lTime = time(NULL);
		sTime = (unsigned) lTime/2;
		data->seed = sTime;
		//srand(data->seed);

		if(pthread_create(&(sensors[i]), NULL, (void *)sensor_struct, data) != 0){
			perror("pthread_create");
			exit(1);
		}
	}

	//__________________________________________
	//__________________________________________
	//print out temperature_List and its average
	//eraseList(temperature_List);
	//__________________________________________
	//__________________________________________

	for(i=0; i<numSensors; i++){
		pthread_join(sensors[i], NULL);
	}

	return 0;
}

void canIAdd(int id){
	//while i can't go
	pthread_cond_wait(&self, &locker);
	//end loop
	return;
}

void addTemp(int id){
	pthread_mutex_lock(&locker);
	printf("Sensor #%d is adding a temperature...", id);
	//while cant go, wait -- have this checking in sensor (thread) function

	myNode = createNode(sensors[id]->seed);//parameter==temp
	insert(temperature_List, myNode);
	
	pthread_mutex_unlock(&locker);
	return;
}

void sensor(sensor_struct * data){
	printf("This is sensor #%d", data->id);
	//while cant go wait ----->canIAdd(data->id);
	srand(data->seed);
	temp = rand()%100;
	addTemp(data->id);
	//pthread_cond_broadcast(&self);
	pthread_exit(NULL);
}