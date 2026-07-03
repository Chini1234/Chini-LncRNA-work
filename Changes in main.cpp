Replace the following:
1. string readRna(string rnaFileName,string &lncName);   (Delete)
1. void readRnaMulti(const string &rnaFileName,
                  vector<pair<string,string>> &rnaList);   (Replace)

2. string readRna(...)
{
   ...
}      (Del)

2. void readRnaMulti(const string &rnaFileName,
                  vector<pair<string,string>> &rnaList)
{
    ifstream rnaFile(rnaFileName.c_str());

    if(!rnaFile.is_open())
    {
        cerr << "Cannot open RNA file: " << rnaFileName << endl;
        exit(1);
    }

    string line;
    string name;
    string seq;

    while(getline(rnaFile,line))
    {
        if(line.empty())
            continue;

        if(line[0]=='>')
        {
            if(!name.empty())
            {
                rnaList.push_back(make_pair(name,seq));
            }

            name=line.substr(1);
            seq.clear();
        }
        else
        {
            seq+=line;
        }
    }

    if(!name.empty())
    {
        rnaList.push_back(make_pair(name,seq));
    }

    rnaFile.close();
}       (Replace)


3. string lncName;
string lncSeq;

3. vector<pair<string,string>> rnaList;

4. lncSeq=readRna(paraList.file2path,lncName);
4. readRnaMulti(paraList.file2path,rnaList);

5. lncName.erase(remove(lncName.begin(),lncName.end(),'\r'),lncName.end());
lncName.erase(remove(lncName.begin(),lncName.end(),'\n'),lncName.end());

resultDir=paraList.outpath;

struct lgInfo algInfo;

algInfo=lgInfo(
    lncName,
    lncSeq,
    species,
    dnaChroTag,
    fileName,
    dnaSeq,
    startGenome,
    resultDir);

lgList.push_back(algInfo);

5. resultDir=paraList.outpath;

for(size_t k=0;k<rnaList.size();k++)
{
    string lncName=rnaList[k].first;
    string lncSeq=rnaList[k].second;

    lncName.erase(remove(lncName.begin(),lncName.end(),'\r'),
                  lncName.end());

    lncName.erase(remove(lncName.begin(),lncName.end(),'\n'),
                  lncName.end());

    lgInfo info(
        lncName,
        lncSeq,
        species,
        dnaChroTag,
        fileName,
        dnaSeq,
        startGenome,
        resultDir);

    lgList.push_back(info);
}

6. int i=0;

vector<triplex> sort_triplex_list;

LongTarget(
    paraList,
    lgList[i].lncSeq,
    lgList[i].dnaSeq,
    sort_triplex_list);

printResult(
    lgList[i].species,
    paraList,
    lgList[i].lncName,
    lgList[i].fileName,
    sort_triplex_list,
    lgList[i].dnaChroTag,
    lgList[i].dnaSeq,
    lgList[i].startGenome,
    c_tmp_dd,
    c_tmp_length,
    lgList[i].resultDir);

6. for(size_t i=0;i<lgList.size();i++)
{
    cout << "==================================" << endl;
    cout << "Processing RNA: "
         << lgList[i].lncName << endl;
    cout << "==================================" << endl;

    vector<triplex> sort_triplex_list;

    LongTarget(
        paraList,
        lgList[i].lncSeq,
        lgList[i].dnaSeq,
        sort_triplex_list);

    printResult(
        lgList[i].species,
        paraList,
        lgList[i].lncName,
        lgList[i].fileName,
        sort_triplex_list,
        lgList[i].dnaChroTag,
        lgList[i].dnaSeq,
        lgList[i].startGenome,
        c_tmp_dd,
        c_tmp_length,
        lgList[i].resultDir);
}
