#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 1;
    }

    // TODO: Declare data structures to track bid statistics for each item
    // You need to track: total bids, successful bids, rejected bids for each item
    // Hint: You may use additional BSTs or other data structures
    // Start your code here
    ListBST<string,int>auctionBST;
    ListBST<string,int>totalBST;
    ListBST<string,int>successBST;
    ListBST<string,int>rejectedBST;

    ListBST<string,int>trackBST;
    // End your code here

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i) 
    {
        // TODO: Implement the logic to read initial items and their starting bids
        string ID;
        int startBid;
        in_file>>ID>>startBid;
        // Initialize statistics tracking for each item
        // Start your code here
        auctionBST.insert(ID,startBid);
        totalBST.insert(ID,0);
        successBST.insert(ID,0);
        rejectedBST.insert(ID,0);

        trackBST.insert(ID,0);
        // End your code here
    }

    // TODO: Implement the logic to print the initial auction state
    // Start your code here
    cout<<"Initial auction items:"<<endl;
    cout<<"BST (In-order): ";
    auctionBST.print('I');    cout<<endl;    // End your code here
    cout << "\nAuction starts!\n\n";
    cout << "==============================\n";

    string operation;
    int net_bids=0;
    int net_success=0;
    int net_fail=0;
    while (in_file >> operation) {
        // TODO: Implement the logic to process operations (ADD, BID, CHECK, STATS, REPORT) and print auction state after each operation
        if(operation=="ADD")
        {
            string ID;
            int startBid;
            in_file>>ID>>startBid;
            if(auctionBST.find(ID)==true)
            {
                if(auctionBST.get(ID)<startBid)
                {
                    auctionBST.update(ID,startBid);
                }
            }
            else
            {
                auctionBST.insert(ID,startBid);
                totalBST.insert(ID,0);
                successBST.insert(ID,0);
                rejectedBST.insert(ID,0);
                trackBST.insert(ID,0);
                cout<<"Item "<< ID <<" added with starting bid "<< startBid<<endl; 
            }
            cout<<"BST (In-order): ";
            auctionBST.print('I');
            cout<<endl;
        }
        else if(operation=="BID")
        {
            string ID;
            int bid_amount;
            in_file>>ID>>bid_amount;
            if(auctionBST.find(ID)==false)
            {
                cout<<"Item Not Added.Cannot Place A Bid."<<endl;
            }
            else
            {
                if(bid_amount<=auctionBST.get(ID))
                {
                    rejectedBST.update(ID,rejectedBST.get(ID)+1);
                    cout<<"Bid of "<<bid_amount<<" on "<<ID<<" rejected. Current bid: "<<auctionBST.get(ID)<<endl;
                    cout<<"BST (In-order): ";
                    auctionBST.print('I');
                    cout<<endl;
                    net_fail++;
                }
                else
                {
                    auctionBST.update(ID,bid_amount);
                    successBST.update(ID,successBST.get(ID)+1);
                    net_success++;
                    cout<<"Bid of "<<bid_amount<<" on "<<ID<<" accepted. Current bid: "<<auctionBST.get(ID)<<endl;
                    cout<<"BST (In-order): ";
                    auctionBST.print('I');
                    cout<<endl;
                }
                totalBST.update(ID,totalBST.get(ID)+1);
                net_bids++;
            }
        }
        else if(operation=="CHECK")
        {
            string ID;
            in_file>>ID;
            if(auctionBST.find(ID)==true)
            {
                cout<<"Current bid for "<<ID<<": "<<auctionBST.get(ID)<<endl;
                cout<<"BST (In-order): ";
                auctionBST.print('I');
                cout<<endl;
            }
            else
            {
                cout<<"Item Not Found"<<endl;
            }
        }
        else if(operation=="STATS")
        {
            string ID;
            in_file>>ID;
            if(auctionBST.find(ID)==true)
            {
                cout<<"Statistics for "<<ID<<":"<<endl;
                cout<<"  Current highest bid: "<<auctionBST.get(ID)<<endl;
                cout<<"  Total bids placed: "<<totalBST.get(ID)<<endl;
                cout<<"  Successful bids: "<<successBST.get(ID)<<endl;
                cout<<"  Rejected bids: "<<rejectedBST.get(ID)<<endl;
            }
            else
            {
                cout<<"Item not found"<<endl;
            }
        }
        else if(operation=="REPORT")
        {
            cout<<"Auction Report:"<<endl;
            cout<<"Total items: "<< auctionBST.size()<<endl;
            cout<<"Total bids placed: "<<net_bids<<endl;
            cout<<"Total successful bids: "<<net_success<<endl;
            cout<<"Total rejected bids: "<<net_fail<<endl<<endl;
            cout<<"Item Statistics:"<<endl;

            ListBST<string,int>tempBST;
            while(trackBST.size()>0)
            {
                string minID=trackBST.find_min();
                tempBST.insert(minID,0);
                trackBST.remove(minID);
            }
            while(tempBST.size()>0)
            {
                string ID=tempBST.find_min();
                cout<<"  "<<ID<<": Current bid: "<<auctionBST.get(ID)<<", Total bids: "<<totalBST.get(ID)<<", Successful: "<<successBST.get(ID)<<", Rejected: "<<rejectedBST.get(ID)<<endl;
                trackBST.insert(ID, 0);
                tempBST.remove(ID);
            }
        }
        else
        {
            cout<<"Invalid Operation"<<endl;
        }
        // For BID operations: update statistics (total bids, successful/rejected counts)
        // For STATS operations: display statistics for the specified item
        // For REPORT operations: display comprehensive auction statistics
        // For other operations: print auction state using in-order traversal
        // Start your code here

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    // TODO: Delete data structures you created
    // Start your code here
    auctionBST.clear();
    totalBST.clear();
    successBST.clear();
    rejectedBST.clear();
    trackBST.clear();
    // End your code here
    return 0;
}
