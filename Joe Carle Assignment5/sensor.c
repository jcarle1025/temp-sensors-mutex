#include "linkedList.h"
#include "pthread.h"
#include <sys/types.h>

int numSensors,numCycles, *temp;
linkedList temperature_List;
node myNode, tempNode;
int sTime;
long lTime;

pthread_mutex_t locker;

typedef struct {
	int id;
	int seed;
}sensor_struct;

void sensor(sensor_struct * data);
void addTemp(int id, int seed);

int main(int argc, char *argv[]){
	temperature_List = makeLL();
	int i,a;
	sensor_struct *data;

	//to run --> ./nameofMain #sensors #cycles
	if(argc != 3){
		puts("ERROR! Format should be: ./sensor #ofSensors #ofCycles\n");
		exit(0);
	}

	numSensors = atoi(argv[1]); 
	numCycles = atoi(argv[2]);
	printf("Running %d cycle(s) on %d sensor(s)\n\n", numCycles,numSensors);
	
	pthread_t sensors[numSensors];
	pthread_mutex_init(&locker, NULL);
	
	//fills, prints, and gets average of LL a user specified number of times
	for(a=1; a<=numCycles; a++){
		printf("CYCLE %d:\n", a);
		
		for(i=1; i<=numSensors; i++){
			data = (sensor_struct*)malloc(sizeof(sensor_struct));
			data->id = i;
			lTime = time(NULL);
			sTime = (unsigned) lTime/2;
			data->seed = sTime;

			//creates new sensor thread in array --> inserts newly generated temperature
			if(pthread_create(&(sensors[i]), NULL, (void *)sensor, data) != 0){
				perror("pthread_create");
				exit(1);
			}
		}

		sleep(1);

		traverse(temperature_List);
		average(temperature_List);
		eraseList(temperature_List);
	}
	
	//waiting for all sensor threads to terminate
	for(i=1; i<=numSensors; i++){
		pthread_join(sensors[i], NULL);
	}
	
	printf("All done. Goodbye\n");
	return 0;
}

//protects LL with mutex and adds random temperatures
void addTemp(int id, int seed){
	pthread_mutex_lock(&locker);
	printf("Sensor #%d is adding a temperature...", id);
	
	//critical section --> creating random temperature node and inserting to LL
	temp = (int*)malloc(sizeof(int));
	srand((rand()%50)*seed);
	*temp = rand()%100;
	myNode = createNode(temp);
	insert(temperature_List, myNode);
	
	pthread_mutex_unlock(&locker);
	return;
}

//sensor thread function
void sensor(sensor_struct * data){
	lTime = time(NULL);
	sTime = (unsigned) lTime/2;
	addTemp(data->id, data->seed);
	pthread_exit(NULL);
}
