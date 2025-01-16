#include "csvstream.hpp"
#include <set>
#include <cmath>
using namespace std;

ostream& operator<<(ostream &out, const map<string,int> &words){
    for(const auto &kv :words){
        const auto &word = kv.first; //key
        auto number = kv.second; //value
        out << word <<" "<<number<<endl;
        
    }
    return out;
}
ostream& operator<<(ostream &out, const map<pair<string,string>,int> &words){
    for(const auto &kv :words){
        const auto &label = kv.first.first; //key pt1: label
        const auto &word = kv.first.second; //key p2: word
        auto number = kv.second; //value
        out << label <<":"<< word <<" "<<number<<endl;
        
    }
    return out;
}

class Classifier{
private:
    int numPosts = 0;
    int vocabSize =0; //vocabCount.size()
    map<string,int> vocabCount; //has length vocabSize 
    map<string,int> labelCounts; //how many posts had Label
    map<pair<string,string>,int> cHasW; 
    //label,word. int posts with Label have Word

    map<string,double> lnCScores; //label,log-probability 
    map<pair<string,string>,double> lnCWScores;


    int correct = 0;
    int testPosts = 0;
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }
    void processRow(const string &label ,const string &content){
        set<string> contents = unique_words(content); 
        //gets only unique words "bag of words" style
        for(auto it = contents.begin(); it != contents.end();++it){  
            //iterates through the "bag of words"
            vocabCount[*it]++;   
            //adds 1 to each unique word in vocabCount
            pair<string,string> labeledWord (label,*it);
            cHasW[labeledWord]++;   //adds 1 to each label C with word w
        }
        labelCounts[label]++; 
        //increments the appropriate label 
    }
    void processPrediction(map<string,string> &row){
                    testPosts++;
            string correctLabel = row["tag"];
            string content = row["content"];
            set<string> contents = unique_words(content); 
            map<string,double> probability;
            for(auto it = labelCounts.begin(); it != labelCounts.end(); ++it){ 
                //for each label
                probability[it->first] += lnCScores[it->first]; //add log-prior 
                for(auto it2 = contents.begin(); it2 != contents.end();++it2){  
                    //each word
                    // cout<<"1"<< endl;
                    // cout<<"2"<<endl;
                    // cout<<it->first<<endl;

                    // cout<<"!"<<endl;
                    pair<string,string> labeledWord (it->first,*it2); 
                    
                    if(cHasW[labeledWord] != 0){ //possible error
                        probability[it->first] += lnCWScores[labeledWord];
                   
                    }
                    else if(vocabCount[*it2] != 0){
cHasW.erase(labeledWord);
probability[it->first] += 
log(static_cast<double>(vocabCount[*it2])/static_cast<double>(numPosts));
                  
                    }
                    else if(vocabCount[*it2]==0){
cHasW.erase(labeledWord);
vocabCount.erase(*it2);
probability[it->first] += log(1.0/static_cast<double>(numPosts));
                  
                    }
                    
                }

            }
            auto max = probability.begin();
            for(auto it = probability.begin(); 
            it != probability.end(); ++it){
                 if(max->second < it->second){
                    max = it;
                 }
            }
            cout<<"  correct = "<< correctLabel<<", predicted = "
            <<max->first<<", log-probability score = "<<max->second<<endl;
            cout<<"  content = "<<content<<"\n"<<endl;
            if(correctLabel == max->first){
                correct++;
            }
    }

public:
    void train(const string &in, int argc){ 
        if(argc ==3){
            csvstream stream(in, ',',true);
            map<string,string> row;
            while(stream>>row){
                string label = row["tag"];
                string content = row["content"];
                processRow(label,content);
                numPosts++;
            }
            vocabSize = vocabCount.size();
        }
        else if(argc ==2 ){
            csvstream stream(in, ',',true);
            map<string,string> row;
            cout<<"training data:"<<endl;
            while(stream>>row){
                string label = row["tag"];
                string content = row["content"];
                processRow(label,content);
                cout<<"  label = "<< label<<
                 ", content = "<<content<<endl;
                numPosts++;
            }
            vocabSize = vocabCount.size();
            cout<<"trained on "<<numPosts<< " examples"<<endl;
            cout<<"vocabulary size = "<<vocabSize<<"\n"<<endl;
            // process the training set for the 5 needed things
        }
        else{
            assert(false);
        }
    }

    void trainingTest(){
        cout<<"numPosts: "<<numPosts<< "\n" 
        << "vocabSize: "<<vocabSize<<endl;
        cout<<"\n"<< "labelCounts: \n" <<labelCounts<<endl;
        cout<<"\ncHasW: \n" << cHasW<<endl;
    }
    void calculate(int argc){
        if(argc ==3){
            for(const auto &kv :labelCounts){ //classes section
                const auto &label = kv.first; //key
                auto number = kv.second; //value
                double lnPC = log(number/static_cast<double>(numPosts));

                lnCScores[label]+= lnPC;
            }
            for(const auto &kv : cHasW){
                const auto &label = kv.first.first; //label
                auto number = kv.second; //num of occurances
                double lnPwC = log(number/static_cast<double>(labelCounts[label]));
                
                lnCWScores[kv.first]+=lnPwC;
            }
        }
        else if(argc ==2){
            cout<<"classes:"<<endl;
            for(const auto &kv :labelCounts){ //classes section
                const auto &label = kv.first; //key
                auto number = kv.second; //value
                double lnPC = log(number/static_cast<double>(numPosts));


                cout<<"  "<<label<<", "<<number<< 
                " examples, log-prior = "<< lnPC<<endl;
                lnCScores[label]+= lnPC;
            }
            cout<<"classifier parameters:"<<endl;
            for(const auto &kv : cHasW){
                const auto &label = kv.first.first; //label
                const auto &word = kv.first.second; //word
                auto number = kv.second; //num of occurances
                double lnPwC = log(number/static_cast<double>(labelCounts[label]));
                
                cout<<"  "<<label<<":"<<word<<", count = "
                <<number<<", log-likelihood = "<<lnPwC<<endl; 
                lnCWScores[kv.first]+=lnPwC;
            }
                    cout<<endl;
        }
        else{
            assert(false);
        }

    }

    void predict(const string &in){
        csvstream stream(in, ',',true);
        map<string,string> row;
        map<string,string> junk;
        cout<<"trained on "<< numPosts <<" examples\n\ntest data:"<<endl;
        
        while(stream>>row){//>>row>>row to destroy the junk???
            processPrediction(row);
        }

        cout<<"performance: "<< correct<<
        " / "<<testPosts<<" posts predicted correctly"<<endl;
    }



};
int main(int argc, char **argv) {
    if(!(argc == 3 || argc ==2)){
        cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
        return -1;
    }


    string filename1 = argv[1];
    ifstream fin1(filename1);
    if(!fin1.is_open()){
        cout << "Error opening file: " << filename1 << endl;
        return -1;
    }
    if(argc ==3){
        string filename2 = argv[2];
        ifstream fin2(filename2);
        if(!fin2.is_open()){
            cout << "Error opening file: " << filename2 << endl;
            return -1;
        }
    }
    cout.precision(3);
    Classifier myClassifier;
    myClassifier.train(filename1,argc);
    // myClassifier.trainingTest();
    myClassifier.calculate(argc);
    if(argc ==3){
        string filename2 = argv[2];
        ifstream fin2(filename2);
        if(!fin2.is_open()){
            cout << "Error opening file: " << filename2 << endl;
            return -1;
        }
        myClassifier.predict(filename2);
    }
}

