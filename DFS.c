///////////////////////////////////
/////                         /////
/////   I N C O M P L E T E   /////
/////                         /////
///////////////////////////////////


// Codigo incompleto en c con el algoritmo de DFS para comprobar la conectividad de los bloques de diferencia de PR para
// dividir rectangulos


#define MAX_NUM_RECTANGLES_INSIDE_RECTANGLE 4

#define MIN_PR_TO_SPLIT_RECTANGLE 0.25
#define INITIAL_MAX_CLUSTER_POINTS 200



// ...


int DFS(int const x1, int const y1, int const x2, int const y2, int x, int y, \
           int ***visited_blocks_ref, int *num_clusters_ref, Point **clusters_points_ref, \
           int *max_points_ref, int *current_point_ref){
    int **visited_blocks = *visited_blocks_ref;
    int num_clusters = *num_clusters_ref;
    Point *cluster_points = *clusters_points_ref;
    Point point;

    visited_blocks[y-y1][x-x1] = 1;

    for (int i = y-1; i < y+1; ++i) {
        for (int j = x-1; j < x+1; ++j) {
            if (i>=y1 && y<=y2 && j>=x1 && j<=x2 && get_block_movement(j, i) > MIN_PR_TO_SPLIT_RECTANGLE && \
                !visited_blocks[i-y1][j-x1]) {
                //call DFS of that point
                if (DFS(x1, y1, x2, y2, j, i, visited_blocks_ref, num_clusters_ref, clusters_points_ref, max_cluster_points_ref, current_point_ref)!=0){
                    return -1;
                }
            }
        }
    }
    point.x = x;
    point.y = y;
    if (1+*current_point_ref >= *max_cluster_points_ref) {
        *max_cluster_points_ref += 100;
        cluster_points_ref = realloc(cluster_points_ref, *max_cluster_points_ref * sizeof(*Point));
        if (cluster_points_ref == NULL) {
            printf("ERROR\n");
            return -1;
        }
        cluster_points[current_point_ref] = point;
        current_point_ref++;
    }
    return 0;
}

/**
 *
 */
int split_rectangle_if_not_connected(LinkedRectangle **lr){
    if ((*lr)==NULL) return -1;

    Rectangle *rect = (*lr)->data;
    LinkedRectangle *next = (*lr)->next;
    int frames_not_seen = (*lr)->frames_not_seen;
    int frames_seen = (*lr)->frames_seen;

    int x1 = rect.x1;
    int y1 = rect.y1;
    int x2 = rect.x2;
    int y2 = rect.y2;

    // link :    https://www.geeksforgeeks.org/find-number-of-islands/

    // check rectangle type and do things according to that ??
    // set all blocks to not visited
    // iterate blocks of the rectangle. for each
    //      check if it is over the pr_threshold and if it has not been already visited
    //          apply DFS (Depth First Search) function
    //      if number of clusters is too big stop
    // separate rectangles


    // DFS function should store arrays of conected blocks and append high pr blocks to the cluster they belong
    // it is also interesting to know the number of clusters (number of resulting rectangles instead of the one processed)


    //Point *cluster_points;// array with all the points in the cluster
    
    int num_clusters;                                   // The actual number of clusters
    int *current_points;                                // Number of points in each clusters_points[i] array at each moment
    int max_cluster_points;                             // Number of reserved memory for points in each cluster
    int visited_blocks[y2-y1+1][x2-x1+1];               // Boolean 2D array of visited blocks (+1 due to corners included in the rectangle)
    Point **clusters_points;                            // 2D array.  containing the points of each cluster
    int allocated_clusters;                             // Number of allocated clusters (to free only allocated)

    memset(visited_blocks, 0, sizeof(visited_blocks));  // Set to 0 all the visited_blocks

    cluster_points = malloc(MAX_NUM_RECTANGLES_INSIDE_RECTANGLE * sizeof(*Point));
    if (clusters_points==NULL) return -1;
    int *current_points = malloc(MAX_NUM_RECTANGLES_INSIDE_RECTANGLE * (sizeof(int)));
    if (current_points==NULL) goto FREES_2;
    for (allocated_clusters = 0; allocated_clusters < MAX_NUM_RECTANGLES_INSIDE_RECTANGLE; ++allocated_clusters) {
        clusters_points[allocated_clusters] = malloc(INITIAL_MAX_CLUSTER_POINTS * sizeof(Point));
        if (clusters_points[allocated_clusters]==NULL){
            goto FREES_1;
        }
    }

    num_clusters = 0;
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <=x2; ++x) {
            if (get_block_movement(x, y) > MIN_PR_TO_SPLIT_RECTANGLE && !visited_blocks[i-y1][j-x1]) {
                max_cluster_points = INITIAL_MAX_CLUSTER_POINTS;
                current_points = 0;
                DFS(x1, y1, x2, y2, x, y, &visited_blocks, num_clusters, &clusters_points[num_clusters], &max_cluster_points, &current_points);     // Visit all blocks in this cluster. 
                ++num_clusters;
            }
            if (num_clusters >= MAX_NUM_RECTANGLES_INSIDE_RECTANGLE || num_clusters+num_rects >= MAX_NUM_RECTANGLES) {
                if (TRACE_LEVEL>=1) printf("The rectangle may be split more times, but there is not enough space in the rectangle list\n");
                goto RECTANGLE_SPLITTING_HANDLING;
            }
        }
    }
    RECTANGLE_SPLITTING_HANDLING:
    // TO DO: separar rectangulos con los nuevos datos
    // TO DO: free each clusters_points[i] array, free the clusters_points array
    

    FREES_1:
    for (int j = 0; j < allocated_clusters; ++j) {
        free(clusters_points[j])
    }
    free(current_points);
    FREES_2:
    free(clusters_points);
    if (allocated_clusters<MAX_NUM_RECTANGLES_INSIDE_RECTANGLE) return -1;

    return num_clusters;
}
