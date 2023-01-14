#include "SudokuGenerator.hpp"

void generateSudokuAndInsertTask_use_ATOMIC(DatabaseConnection DB,atomic<int> &successTask,atomic<int> &failTask, int number_of_sudoku){
    for (int i = 0; i<number_of_sudoku;i++){ 
        Sudoku sudoku;
        sudoku.initialize();  
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+sudoku.getFlattenBoard()+"');")==0? successTask.fetch_add(1):failTask.fetch_add(1); // uncomment the deleteData above to avoid duplicates
    }
}

void generateSudokuAndInsertTask_use_MUTEX(DatabaseConnection DB, std::mutex &successTask_mutex, std::mutex &failTask_mutex,int &successTask, int &failTask, int number_of_sudoku){
    for (int i = 0; i<number_of_sudoku;i++){ 
        Sudoku sudoku;
        sudoku.initialize();  
        if (DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+sudoku.getFlattenBoard()+"');") == 0){
            successTask_mutex.lock();
            successTask++;
            successTask_mutex.unlock();
        } else {
            failTask_mutex.lock();
            failTask++;
            failTask_mutex.unlock();
        }
    }
}

void generateSudokuAndInsertTask_use_INT(int x,DatabaseConnection DB,std::vector<int>&successTask,std::vector<int> &failTask, int number_of_sudoku){
    for (int i = 0; i<number_of_sudoku;i++){ 
        Sudoku sudoku;
        sudoku.initialize();  
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+sudoku.getFlattenBoard()+"');")==0? successTask[x]++:failTask[x]++; // uncomment the deleteData above to avoid duplicates
    }
}


void single_thread_sudoku_generator()
{    
    //connect to database
    const char* dir = R"(../Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist(); 
 
    int successTask = 0;
    int failTask = 0;
    //generate and insert 80 sudoku
    for (int i = 0; i<80;i++){
        // generate a sudoku
        Sudoku sudoku;
        sudoku.initialize();   
        DB.insertData("INSERT INTO Sudoku (SudokuValue) Values ('"+sudoku.getFlattenBoard()+"');")==0?successTask++:failTask++; // uncomment the deleteData above to avoid duplicates
    }
 
    //disconnect database
    DB.closeConnection();
    
}

void multi_thread_sudoku_generator_using_ATOMIC()
{
    int NUMBER_OF_THREADS = std::thread::hardware_concurrency();
    //connect to database 
    const char* dir = R"(../Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist();  

    //create vector to hold thread
    vector<std::thread> threadList; 
    


    //create thread and push to vector
    //generate and insert 25 sudoku each thread, 25 * 4 = 100 sudoku in total
     
    //create atomic int fail and success task to hold total number of fail and success task
    std::atomic_int successTask = {0};
    std::atomic_int failTask = {0};
    for (int i = 0;i<NUMBER_OF_THREADS;i++){
        threadList.push_back(std::thread(generateSudokuAndInsertTask_use_ATOMIC,DB, std::ref(successTask), std::ref(failTask), 80/NUMBER_OF_THREADS));
    }   
     

    for (auto& th : threadList) {
        th.join();
    } 
      
    //disconnect database
    DB.closeConnection(); 
}


void multi_thread_sudoku_generator_using_MUTEX()
{
    int NUMBER_OF_THREADS = std::thread::hardware_concurrency();
    //connect to database 
    const char* dir = R"(../Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist();  

    //create vector to hold thread
    vector<std::thread> threadList; 
    


    //create thread and push to vector
    //generate and insert 25 sudoku each thread, 25 * 4 = 100 sudoku in total
     
    //create atomic int fail and success task to hold total number of fail and success task 
    int successTask=0;
    int failTask=0;
    std::mutex successTask_mutex;
    std::mutex failTask_mutex;
    for (int i = 0;i<NUMBER_OF_THREADS;i++){
        threadList.push_back(std::thread(generateSudokuAndInsertTask_use_MUTEX,DB, std::ref(successTask_mutex), std::ref(failTask_mutex), std::ref(successTask), std::ref(failTask), 80/NUMBER_OF_THREADS));
    }
     

    for (auto& th : threadList) {
        th.join();
    }  
     
    //disconnect database
    DB.closeConnection(); 
}


void multi_thread_sudoku_generator_using_INT()
{
    int NUMBER_OF_THREADS = std::thread::hardware_concurrency();
    //connect to database 
    const char* dir = R"(../Database/SudokuDatabase.db)";
    auto DB = DatabaseConnection(dir);
    DB.createTableIfNotExist();  

    //create vector to hold thread
    vector<std::thread> threadList; 
    


    //create thread and push to vector
    //generate and insert 25 sudoku each thread, 25 * 4 = 100 sudoku in total
     
    //create atomic int fail and success task to hold total number of fail and success task
    std::vector<int> successTaskVector(NUMBER_OF_THREADS,0);
    std::vector<int> failTaskVector(NUMBER_OF_THREADS,0);
    for (int i = 0;i<NUMBER_OF_THREADS;i++){
        threadList.push_back(std::thread(generateSudokuAndInsertTask_use_INT,i,DB, std::ref(successTaskVector), std::ref(failTaskVector), 80/NUMBER_OF_THREADS));
    } 
      
    for (auto& th : threadList) {
        th.join();
    } 
 
    int successTask= std::accumulate(successTaskVector.begin(),successTaskVector.end(),0);
    int failTask= std::accumulate(failTaskVector.begin(),failTaskVector.end(),0);

 
    //disconnect database
    DB.closeConnection(); 
}
