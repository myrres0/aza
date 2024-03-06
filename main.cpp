#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <set>


//------------------------------------TASK 1 -----------------------------------//
int find_max_deadline(std::vector<std::vector<int>> shedule){
    int maxDeadline = 0;
    for(auto & i : shedule){
        if(i[1] > maxDeadline){
            maxDeadline = i[1];
        }
    }
    return maxDeadline;
}
int sheduling_with_deadlines(std::vector<std::vector<int>> schedule){

    //sort by decreasing order of profit
    std::sort(schedule.begin(), schedule.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[2] > b[2];
    });

    //find the value of the max deadline
    int maxDeadline = find_max_deadline(schedule);

    //create a vector of size maxDeadline
    std::vector<std::vector<int>> schedulingVector(maxDeadline);
    for (auto & i : schedulingVector) {
        i = {0, 0};
    }


    //fill the vector with the jobs
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = schedule[i][1] - 1; j >= 0; j--) {
            if (schedulingVector[j][0] == 0) {
                schedulingVector[j] = {schedule[i][0], schedule[i][2]};
                break;
            }
        }
    }

    //print the vector
    for(int i = 0; i < schedulingVector.size(); i++){
        std::cout << "Deadline " << i + 1 << " : " << "Job "<<schedulingVector[i][0] <<"; Profit: "<<schedulingVector[i][1]<<std::endl;
    }

    //count the profit
    int profit = 0;
    for(auto & i : schedulingVector){
        profit += i[1];
    }
    std::cout << "Profit : " << profit << std::endl;

    return 0;
}



//------------------------------------TASK 2-----------------------------------//

int find_parent(std::vector<int> disjointSets, int index){
    if(disjointSets[index] == index){
        return index;
    }
    return find_parent(disjointSets, disjointSets[index]);
}

std::vector<int>union_sets(std::vector<int> disjointSets, int index1, int index2){
    int parent1 = find_parent(disjointSets, index1);
    int parent2 = find_parent(disjointSets, index2);
    if(parent1 < parent2){
        disjointSets[parent2] = parent1;
    }
    else{
        disjointSets[parent1] = parent2;
    }
    return disjointSets;
}


int scheduling_with_deadlines_modification(std::vector<std::vector<int>> schedule){

    //sort by decreasing order of profit
    std::sort(schedule.begin(), schedule.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[2] > b[2];
    });

    //find the value of the max deadline
    int maxDeadline = find_max_deadline(schedule);


    std::vector<int> disjointSets(maxDeadline + 1);
    for(int i = 0; i < disjointSets.size(); i++){
        disjointSets[i] = i;
    }

    //for storing final values
    std::vector<std::vector<int>> resultVector(maxDeadline);
    for(int i = 0; i < resultVector.size(); i++){
        resultVector[i] = {0, 0};
    }


    int job = 0;
    for (int i = 0; i < schedule.size(); i++) {
        int parent = find_parent(disjointSets, schedule[i][1]);
        if (parent > 0) { //if slot is available
            disjointSets = union_sets(disjointSets, parent, parent - 1); //union the sets
            resultVector[parent - 1] = {schedule[i][0], schedule[i][2]}; //fill the result vector
        }
    }


    int profit = 0;
    //print the result
    for(int i = 0; i < resultVector.size(); i++){
        std::cout << "Deadline " << i+1 << " : " << "Job: "<<resultVector[i][0] <<"; Profit:"<<resultVector[i][1]<<std::endl;
        profit += resultVector[i][1];
    }
    std::cout<< "Profit : " << profit << std::endl;
    return 0;
}


//* ------------------------------------TASK 3 (Greedy algorithm)------------------------------------//
int greedyAlgorithm(std::vector<std::vector<int>> task3Vector){

    std::map<std::string, int> task3ResultMap; // for printing results
    std::vector<int> blockedRows; // controling the used rows

    for(int i = 0; i < task3Vector[0].size();i++){
        bool isInitialised = false; // check if min is initialised
        int min;
        int minRow;
        for(int j = 0; j < task3Vector.size(); j++){
            auto it = std::find(blockedRows.begin(), blockedRows.end(), j); //iterator to find j in blockedRows
            if(it != blockedRows.end()){ //if j is in blockedRows
                continue;
            }
            if(!isInitialised){ // if min is not initialised
                min = task3Vector[j][i];
                minRow = j;
                isInitialised = true;
            }
            if(task3Vector[j][i] < min){
                min = task3Vector[j][i];
                minRow = j;
            }
        }
        task3ResultMap["Job " + std::to_string(i+1)] = min;
        blockedRows.push_back(minRow); // adding used row to blockedRows
    }
    //printing results
    for (const auto& pair : task3ResultMap) {
        std::cout << pair.first << " : " << "min cost is "<<pair.second << std::endl;
    }
    return 0;
}



//------------------------------------TASK 4 (Hungarian algorithm)------------------------------------//

int find_min_in_vector(std::vector<int>task3Vector){
    int min = task3Vector[0];
    for(int i = 0; i < task3Vector.size(); i++){
        if(task3Vector[i] < min){
            min = task3Vector[i];
        }
    }
    return min;
}

std::vector<std::vector<int>> substractMinValue(std::vector<std::vector<int>>task3Vector, std::set<int> coveredRows, std::set<int> coveredColumns){
    //find min uncovered element
    int min = 1000;
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector[i].size(); j++){
            auto it = coveredRows.find(i);
            auto it2 = coveredColumns.find(j);
            if(it == coveredRows.end() && it2 == coveredColumns.end()){
                if(task3Vector[i][j] < min){
                    min = task3Vector[i][j];
                }
            }
        }
    }

    //subtract min from uncovered elements and add min to elements covered by two lines
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector[i].size(); j++){
            auto it = coveredRows.find(i);
            auto it2 = coveredColumns.find(j);
            if(it == coveredRows.end() && it2 == coveredColumns.end()){
                //subtract min from uncovered elements
                task3Vector[i][j] -= min;
            }
            if(it != coveredRows.end() && it2 != coveredColumns.end()){
                //add min to elements covered by two lines
                task3Vector[i][j] += min;
            }
        }
    }
    return task3Vector;
}

int find_index_num(std::vector<int> array, int num){
    for(int i = 0; i < array.size(); i++){
        if(array[i] == num){
            return i;
        }
    }
    return -1;
}
std::tuple<int, std::set<int>, std::set<int>> find_min_lines(std::vector<std::vector<int>> task3Vector){
    //hungarian algorithm to find min lines to cover zeros
    std::set<int> coveredRows;
    std::set<int> coveredColumns;

    //mark first 0 in each row with *
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector.size();j++) {
            if (task3Vector[i][j] == 0) {
                auto it = coveredColumns.find(j);
                if (it == coveredColumns.end()) { //if j is not in coveredColumns
                    coveredColumns.insert(j);
                    task3Vector[i][j] = -1;
                    break;
                }
            }
        }
    }

    if(coveredColumns.size() == task3Vector.size()){
        return std::make_tuple(coveredColumns.size(), coveredColumns, coveredRows);
    }

    //find 0 in columns that are not covered by *
    for(int i = 0; i< task3Vector.size();i++){
        for(int j = 0; j < task3Vector.size();j++){
            if(task3Vector[i][j] == 0){
                auto starredCols = coveredColumns.find(j);
                auto starredRows = coveredRows.find(i);
                //if j is not in coveredRows and coveredColumns
                if(starredRows == coveredRows.end() && starredCols == coveredColumns.end()){
                    task3Vector[i][j] = -2; // prime a zero
                }
            }
        }
    }

    //change covered cols and rows
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector.size();j++){
            if(task3Vector[i][j]==-2) {
                int starred_zero_index = find_index_num(task3Vector[i], -1);
                if (starred_zero_index != -1) { //if primed zero and starred zero are in the same row
                    coveredRows.insert(i); // cover the row
                    //uncover the column
                    auto it = coveredColumns.find(starred_zero_index);
                    //coveredColumns.erase(it);
                    if (it != coveredColumns.end()) {
                        // Erase the element
                        coveredColumns.erase(it);

                    }
                }
            }
        }
    }

    //step for finding all zeros
    std::set<std::vector<int>> primedZeros;
    std::set<std::vector<int>> starredZeros;
    int col=-1;
    do {
        if(col == -1) {
            for (int i = 0; i < task3Vector.size(); i++) {
                for (int j = 0; j < task3Vector.size(); j++) {
                    if (task3Vector[i][j] == 0) {
                        task3Vector[i][j] = -2;
                        primedZeros.insert({i, j});
                        col = j;
                        break;
                    }
                }
            }
        }
        int row = -1;
        if (col != -1) {
            for (int i = 0; i < task3Vector.size(); i++) {
                if (task3Vector[i][col] == -1) {
                    starredZeros.insert({i, col});
                    row = i;
                    break;
                }
                col = -1;
            }
        }
        //if we found primed zero in the same row
        if( row != -1){
            for(int j = 0; j < task3Vector.size();j++){
                if(task3Vector[row][j] == -2){
                    primedZeros.insert({row,j});
                    col = j;
                    break;
                }
                col = -1;
            }
        }
        if(row == -1){
            col = -1;
        }

    }while(col != -1);

    coveredColumns.clear();
    coveredRows.clear();
    //change all primed zeros to starred zeros and vice versa
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector[i].size(); j++){
            auto it = primedZeros.find({i,j});
            auto it2 = starredZeros.find({i,j});
            if(it!= primedZeros.end()){
                task3Vector[i][j] = -1;
            }
            if(it2 != starredZeros.end()){
                task3Vector[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector[i].size(); j++){
            if(task3Vector[i][j]==-1){
                coveredColumns.insert(j);
            }
        }
    }

    //change covered cols and rows
    for(int i = 0; i < task3Vector.size();i++){
        for(int j = 0; j < task3Vector.size();j++){
            if(task3Vector[i][j]==-2) {
                int starred_zero_index = find_index_num(task3Vector[i], -1);
                if (starred_zero_index != -1) { //if primed zero and starred zero are in the same row
                    coveredRows.insert(i); // cover the row
                    //uncover the column
                    auto it = coveredColumns.find(starred_zero_index);
                    //coveredColumns.erase(it);
                    if (it != coveredColumns.end()) {
                        // Erase the element
                        coveredColumns.erase(it);
                    }
                }
            }
        }
    }
    return std::make_tuple(coveredColumns.size() + coveredRows.size(), coveredColumns, coveredRows);
}

//hungarian algorithm
std::set<std::vector<int>> dynamic_approach(std::vector<std::vector<int>> task3Vector){

    //subtracting min from rows
    for(int i = 0; i < task3Vector.size();i++){
        int min = find_min_in_vector(task3Vector[i]);
        for(int j = 0; j < task3Vector[i].size(); j++){
            task3Vector[i][j] -= min;
        }
    }

    //subtracting min from columns
    for(int i = 0; i < task3Vector.size();i++){
        int min = task3Vector[0][i];
        for(int j = 0; j < task3Vector.size(); j++){
            if(task3Vector[j][i] < min){
                min = task3Vector[j][i];
            }
        }
        for(int j = 0; j < task3Vector.size(); j++){
            task3Vector[j][i] -= min;
        }
    }


    int min_lines = std::get<0>(find_min_lines(task3Vector));

    while(min_lines!=task3Vector.size()){
        std::set<int> coveredRows;
        std::set<int> coveredColumns;
        std::tie(min_lines, coveredColumns, coveredRows) = find_min_lines(task3Vector);
        task3Vector = substractMinValue(task3Vector, coveredRows, coveredColumns);
        min_lines = std::get<0>(find_min_lines(task3Vector));
        std::cout << "min_lines = " << min_lines << std::endl;
    }

    std::set<std::vector<int>> resultCoordinates;
    std::set<int> blockedColumns;
    std::set<int> blockedRows;


    //loop for finding the result
    while(resultCoordinates.size()!=task3Vector.size()){
        std::map<int, int> zerosInRows;
        std::map<int, int> zerosInColumns;

        //count zeros in each row and column
        for(int i = 0; i < task3Vector.size();i++){
            auto it = blockedRows.find(i);
            if(it != blockedRows.end()){ //if i is in blockedRows
                continue;
            }
            for(int j = 0; j < task3Vector.size(); j++){
                auto it2 = blockedColumns.find(j);
                if(it2 != blockedColumns.end()){ //if j is in blockedColumns
                    continue;
                }
                if(task3Vector[i][j] == 0){
                    zerosInRows[i] += 1 ;
                    zerosInColumns[j] += 1;
                }
            }
        }

        auto minValueInRows = std::min_element(
                zerosInRows.begin(),
                zerosInRows.end(),
                [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                return p1.second < p2.second;
        });

        auto minValueInColumns = std::min_element(
                zerosInColumns.begin(),
                zerosInColumns.end(),
                [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                return p1.second < p2.second;
        });

        if(minValueInRows->second <= minValueInColumns->second){
            int coordI = minValueInRows->first;
            int coordJ = -1;
            for(int j = 0; j < task3Vector.size(); j++){
                auto it = blockedColumns.find(j);
                if(it != blockedColumns.end()){ //if j is in blockedColumns
                    continue;
                }
                if(task3Vector[coordI][j] == 0){
                    coordJ = j;
                    break;
                }
            }
            blockedRows.insert(coordI);
            blockedColumns.insert(coordJ);
            resultCoordinates.insert({coordI, coordJ});
        }
        else{
            int coordJ = minValueInColumns->first;
            int coordI = -1;
            for(int i = 0; i < task3Vector.size(); i++){
                auto it = blockedRows.find(i);
                if(it != blockedRows.end()){ //if i is in blockedRows
                    continue;
                }
                if(task3Vector[i][coordJ] == 0){
                    coordI = i;
                    break;
                }
            }
            blockedColumns.insert(coordJ);
            blockedRows.insert(coordI);
            resultCoordinates.insert({coordI, coordJ});
        }
        zerosInRows.clear();
        zerosInColumns.clear();
    }

    return resultCoordinates;
}





//------------------------------------MAIN-----------------------------------//
int main() {
    std::vector<std::vector<int>> task3Vector;
    task3Vector = {
            //J1 J2 J3
            {10, 5, 5},
            {2, 4, 10},
            {5, 1, 7}
    };
    std::vector<std::vector<int>> shedululingVector;

    shedululingVector = {
            {1, 2, 40}, //first element stand for job number, second for deadline, third for profit
            {2, 4, 15},
            {3, 3, 60},
            {4, 2, 20},
            {5, 3, 10},
            {6, 1, 45},
            {7, 1, 55}
    };

    std::cout << "---------------------------Task 1---------------------------" << std::endl;
    sheduling_with_deadlines(shedululingVector);

    std::cout << "---------------------------Task 2---------------------------" << std::endl;
    scheduling_with_deadlines_modification(shedululingVector);

    std::cout << "---------------------------Task 3---------------------------" << std::endl;
    greedyAlgorithm(task3Vector);

    std::cout << "---------------------------Task 4---------------------------" << std::endl;
    auto results= dynamic_approach(task3Vector);
    for (auto & i : results) {
        std::cout<<"Job "<<i[1]+1<<": "<<"min cost:"<<task3Vector[i[0]][i[1]]<<std::endl;

    }
    return 0;
}




