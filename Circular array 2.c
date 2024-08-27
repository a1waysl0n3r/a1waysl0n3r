    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAX_STRING_LENGTH 6

    struct package
    {
        char* id;
        int weight;
    };

    typedef struct package package;

    struct post_office
    {
        int min_weight;
        int max_weight;
        package* packages;
        int packages_count;
    };

    typedef struct post_office post_office;

    struct town
    {
        char* name;
        post_office* offices;
        int offices_count;
    };

    typedef struct town town;



    void print_all_packages(town t){
        printf("%s:", t.name);
        for(int i = 0; i < t.offices_count; i++){
            printf("\t%d:", i);
            for(int j = 0; j < t.offices[i].packages_count; j++)
                printf("\t\t%s", t.offices[i].packages[j].id);
        }

    }

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
        int source_package_lost = 0;
        int target_package_added = 0;
        int new_packages_count = 0;

        int target_right = target->offices[target_office_index].packages_count - 1;

        post_office* srce = source->offices[source_office_index];

        post_office* trgt = target->offices[target_office_index];

        trgt->packages = realloc(trgt->packages,sizeof(package)*(srce->packages_count + trgt->packages_count));

        for(int i = 0; i < srce->packages_count; i++){

           for(int j = 0; j < srce->packages_count; j++ ){

                package* srce_pkg = srce->packages[j];
                package* trgt_pkg = trgt->packages[j];

                if(srce_pkg->weight >= trgt->min_weight && srce_pkg->weight <= trgt->max_weight){

                        target->offices[target_office_index].packages[++target_right] = source->offices[source_office_index].packages[j];
                        target_package_added += 1;
                        source_package_lost += 1;

                }
           }
        source->offices[source_office_index].packages_count -= source_package_lost;
        target->offices[target_office_index].packages_count -= target_package_added;
        }






    }

town town_with_most_packages(town* towns, int towns_count){
            int max = 0;
            int num[towns_count];
            int max_id;
            int total_package = 0;
            for(int i = 0; i < towns_count; i++){
                for(int j = 0; j < towns->offices_count; j++){
                    total_package = total_package + towns[i].offices[j].packages_count;
                }
                num[i] = total_package;
                if(total_package > max){
                    max = total_package;
                    total_package = 0;
                }
                else{
                    total_package = 0;
                }

            }
            for(int k = 0; k < towns_count; k++){
                if(num[k]==max){
                    max_id = k;
            }
        }
        return towns[max_id];
}



town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return NULL; // Return NULL if no matching town is found
}

    int main()
    {
        int towns_count;
        scanf("%d", &towns_count);
        town* towns = malloc(sizeof(town)*towns_count);
        for (int i = 0; i < towns_count; i++) {
            towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
            scanf("%s", towns[i].name);
            scanf("%d", &towns[i].offices_count);
            towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
            for (int j = 0; j < towns[i].offices_count; j++) {
                scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
                towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
                for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                    towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                    scanf("%s", towns[i].offices[j].packages[k].id);
                    scanf("%d", &towns[i].offices[j].packages[k].weight);
                }
            }
        }
        int queries;
        scanf("%d", &queries);
        char town_name[MAX_STRING_LENGTH];
        while (queries--) {
            int type;
            scanf("%d", &type);
            switch (type) {
            case 1:
                scanf("%s", town_name);
                town* t = find_town(towns, towns_count, town_name);
                print_all_packages(*t);
                break;
            case 2:
                scanf("%s", town_name);
                town* source = find_town(towns, towns_count, town_name);
                int source_index;
                scanf("%d", &source_index);
                scanf("%s", town_name);
                town* target = find_town(towns, towns_count, town_name);
                int target_index;
                scanf("%d", &target_index);
                send_all_acceptable_packages(source, source_index, target, target_index);
                break;
            case 3:
                printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
                break;
            }
        }
        return 0;
    }

