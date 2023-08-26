#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

class BSTNode
{
public:
    int data;
    bool visited;
    BSTNode* right;
    BSTNode* left;
public:
    BSTNode(int data) : data(data), right(nullptr), left(nullptr), visited(false) {}
    void Visit()
    {
        cout << this->data << " ";
    }
};

class BSTTree
{
public:
    BSTNode* root;
public:
    BSTTree() : root(nullptr) {}
    //void printBT(const BSTNode* node);



    void printBT(const string& prefix, const BSTNode* node, bool isLeft)
    {
        if (node != nullptr)
        {
            printBT(prefix + (isLeft ? "    " : "|   "), node->right, false);

            cout << prefix;

            cout << (isLeft ? "|---" : "|---");

            // print the value of the node
            cout << node->data << std::endl;

            printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        }
    }

    void printBT(const BSTNode* node)
    {
        printBT("", node, false);
    }

    void IterativeInsert(int data)
    {
        BSTNode* newNode = new BSTNode(data);
        if (root == nullptr)
        {
            root = newNode;
        }
        else
        {
            BSTNode* prev = nullptr;
            BSTNode* curr = root;
            while (curr != nullptr)
            {
                prev = curr;
                if (data <= curr->data)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            if (data <= prev->data)
                prev->left = newNode;
            else
                prev->right = newNode;
        }
    }

    BSTNode* IterativeSearch(int value)
    {
        BSTNode* curr = root;
        if (root == nullptr)
            return nullptr;
        if (root->right == nullptr && root->left == nullptr && root->data != value)
            return nullptr;
        while (curr != nullptr)
        {
            if (curr->data == value)
                return curr;
            else if (value < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return nullptr;

    }

    void Insert(BSTNode* p, int data)
    {
        if (p == nullptr)
            p = new BSTNode(data);
        return;
        if (data <= p->data)
            Insert(p->left, data);
        else
            Insert(p->right, data);

    }

    BSTNode* FindMin(BSTNode* root)
    {
        if (root->left == nullptr)
            return root;
        return FindMin(root->left);
    }

    bool Search(BSTNode* p, int data)
    {
        if (p == nullptr)
            return 0;
        else if (p->data == data)
            return 1;

        if (data <= p->data)
            Search(p->left, data);
        else
            Search(p->right, data);
    }

    BSTNode* findMin(BSTNode* p)
    {
        if (p->left == nullptr)
            return p;
        findMin(p->left);
    }
    BSTNode* findMax(BSTNode* p)
    {
        if (p->right == nullptr)
            return p;
        findMax(p->right);
    }
    void iterativePreorder()
    {
        stack<BSTNode*> myStack;
        BSTNode* p = root;
        if (p != nullptr)
            myStack.push(p);

        while (!myStack.empty())
        {
            p = myStack.top();
            p->Visit();
            myStack.pop();
            if (p->right != nullptr)
                myStack.push(p->right);
            if (p->left != nullptr)
                myStack.push(p->left);
        }
    }

    void iterativeInorder()
    {
        stack<BSTNode*> myStack;
        BSTNode* p = root;
        while (p != nullptr) //obradjuje svako podstablo u stablu (ukljucujuci i celo stablo)
        {
            while (p != nullptr)
            {
                if (p->right != nullptr)
                    myStack.push(p->right);
                myStack.push(p);
                p = p->left;
            } //dodje se do kraja skroz levo
            p = myStack.top();
            myStack.pop();
            while (!myStack.empty() && p->right == nullptr) //OVO OBRADJUJE SVE STO NEMA DESNO PODSTABLO ODJEDNOM
            {
                p->Visit();
                p = myStack.top();
                myStack.pop();
            }
            p->Visit(); //obradi se taj sto ima desno podstablo
            if (!myStack.empty()) // i prelazi se na to desno podstablo (na vrhu steka je)
            {
                p = myStack.top();
                myStack.pop();
            }
            else
                p = NULL; // ako ga nema
        }
    }

    void iterativePostorder(BSTNode* p)
    {
        stack<BSTNode*> stack;
        BSTNode* curr;
        stack.push(p);
        if (p == nullptr)
            return;
        while (!stack.empty())
        {
            curr = stack.top();
            if ((curr->left == nullptr || curr->left->visited == true) && (curr->right == nullptr || curr->right->visited == true))
            {
                curr->Visit();
                curr->visited = true;
                stack.pop();
                continue;
            }
            if (curr->right != nullptr)
                stack.push(curr->right);
            if (curr->left != nullptr)
                stack.push(curr->left);
        }
    }

    void Preorder(BSTNode* root)
    {
        if (root == nullptr)
            return;
        root->Visit();
        Preorder(root->left);
        Preorder(root->right);

    }
    void Inorder(BSTNode* root)
    {
        if (root == nullptr)
            return;
        Inorder(root->left);
        root->Visit();
        Inorder(root->right);
    }
    void Postorder(BSTNode* root)
    {
        if (root == nullptr)
            return;
        Postorder(root->left);
        Postorder(root->right);
        root->Visit();

    }

    void levelOrder(BSTNode* root)
    {
        queue<BSTNode*> Q;
        Q.push(root);
        while (!Q.empty())
        {
            BSTNode* curr = Q.front();
            curr->Visit();
            if (curr->left != nullptr)
                Q.push(curr->left);
            if (curr->right != nullptr)
                Q.push(curr->right);
            Q.pop();
        }

    }



    bool isBST(BSTNode* root)
    {
        if (root == nullptr)
            return true;

        if ((root->left == nullptr || root->left->data <= root->data)
            && (root->right == nullptr || root->right->data > root->data))
        {
            if (isBST(root->left) && isBST(root->right))
                return true;
        }
        else
            return false;

        //if (root->left != nullptr && root->left->data > root->data)
        //    return false;
        //if (root->right != nullptr && root->right->data <= root->data)
        //    return false;
        //return (isBST(root->left) && isBST(root->right));
    }

    void isBSTinorder(BSTNode* root, queue<int>& Q)
    {
        if (root == nullptr)
            return;
        isBSTinorder(root->left, Q);
        Q.push(root->data);
        isBSTinorder(root->right, Q);
    }
    bool isIt(BSTNode* root)
    {
        queue<int>Q;
        isBSTinorder(root, Q);
        int i = Q.front();
        Q.pop();
        while (!Q.empty())
        {
            int j = Q.front();
            Q.pop();
            if (i > j)
                return false;
            i = j;
        }
        return true;
    }

    void deleteByCopying(int el)
    {
        BSTNode* curr = root;
        BSTNode* prev = nullptr;
        while (curr != nullptr && curr->data != el)
        {
            prev = curr;
            if (el < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (curr == nullptr)
        {
            return;
        }
        // curr je ptr na cvor koji treba da se obrise, a prev  
        if (curr->left == nullptr && curr->right == nullptr) //nema potomke
        {
            if (prev->left == curr)
                prev->left = nullptr;
            else
                prev->right = nullptr;
            delete curr;
        }
        else if (curr->left == nullptr)
        {
            if (prev->left == curr)
                prev->left = curr->right;
            else
                prev->right = curr->right;
            delete curr;
            return;
        }
        else if (curr->right == nullptr)
        {
            if (prev->left == curr)
                prev->left = curr->left;
            else
                prev->right = curr->left;
            delete curr;
            return;
        }
        else
        {
            BSTNode* parent = curr;
            BSTNode* min = curr->right;
            while (min->left != nullptr)
            {
                parent = min;
                min = min->left;
            }
            curr->data = min->data;
            if (parent == curr)
                parent->right = min->right;
            else
                parent->left = min->right; //ako parent nije root
            delete min;
            return;

        }

    }
    void deleteByCopyingRecursive(BSTNode*& root, int val)
    {
        if (root == nullptr)
            return;
        if (val < root->data)
            deleteByCopyingRecursive(root->left, val);
        else if (val > root->data)
            deleteByCopyingRecursive(root->right, val);
        else // val==root->data
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }
            else if (root->left == nullptr)
            {
                BSTNode* rightChild = root->right;
                delete root;
                root = rightChild;
            }
            else if (root->right == nullptr)
            {
                BSTNode* leftChild = root->left;
                delete root;
                root = leftChild;
            }
            else //ima dva potomka
            {
                BSTNode* min = FindMin(root->right);
                root->data = min->data;
                deleteByCopyingRecursive(root->right, min->data);

            }

        }
    }
    int height(BSTNode* p)
    {
        if (p == nullptr)
            return 0;
        return
            1 + (height(p->left) > height(p->right) ? height(p->left) : height(p->right));
    }
    int countNodes(BSTNode* p)
    {
        if (p == nullptr)
            return 0;
        return 1 + countNodes(p->left) + countNodes(p->right);
    }

    void pass(BSTNode*& ptr)
    {
    }
    int getDepth(BSTNode* p)
    {
        return getDepth2(root, p, 0);
    }
    int getDepth2(BSTNode* p, BSTNode* q, int lvl)
    {
        if (!p) return -1;
        if (p == q) return lvl;
        return max(getDepth2(p->left, q, lvl + 1), getDepth2(p->left, q, lvl + 1));
    }

    //vrati pokazivac na cvor sa maksimalnim zbirom vrednosti svojih direktnih potomaka
    BSTNode* maxSumNodes(BSTNode* p, int& maxSum, BSTNode** maxNode)
    {
        if (p == nullptr)
        {
            maxSum = 0;
            return nullptr;
        }
        int leftSum = 0;
        int rightSum = 0;
        BSTNode* leftMaxSum = maxSumNodes(p->left, leftSum, maxNode);
        BSTNode* rightMaxSum = maxSumNodes(p->right, rightSum, maxNode);

        if (maxSum < (leftSum + rightSum))
        {
            maxSum = leftSum + rightSum;
            *maxNode = p;
        }
        return *maxNode;
    }


    /*==================== B = L = A = N = K = E = T = I ====================*/


    //Junski 2023.
    //Napisati funkciju Node* maxHeightDiff(),koja vraca pokazivac na cvor dinamicki impl. BT sa najvecom
    // razlikom visina levog i desnog podstabla 

    // 1. slabije resenje
    int calcHeight(BSTNode* p)
    {
        if (p == nullptr)
            return 0;
        return
            1 + (calcHeight(p->left) > calcHeight(p->right) ? calcHeight(p->left) : calcHeight(p->right));
    }
    BSTNode* calcMaxHeight(BSTNode* p, int& maxDiff, BSTNode*& maxNode)
    {
        if (p == nullptr)
            return p;
        int diff = abs(calcHeight(p->left) - calcHeight(p->right));
        //maxDiff = (maxDiff > diff ? maxDiff : diff);
        if (diff > maxDiff)
        {
            maxDiff = diff;
            maxNode = p;
        }
        BSTNode* leftSubtreeMaxHeight = calcMaxHeight(p->left, maxDiff, maxNode);
        BSTNode* rightSubtreeMaxHeight = calcMaxHeight(p->right, maxDiff, maxNode);
        return maxNode;
    }

    // 2. bolje resenje
    int calcNew(BSTNode* curr, BSTNode** maxDiffNode, int& maxDiff)
    {
        if (curr == nullptr)
            return 0;

        int leftDepth = calcNew(curr->left, maxDiffNode, maxDiff);
        int rightDepth = calcNew(curr->right, maxDiffNode, maxDiff);
        int diff = abs(leftDepth - rightDepth);

        if (diff > maxDiff)
        {
            maxDiff = diff;
            *maxDiffNode = curr;
        }

        return 1 + max(leftDepth, rightDepth);
    }
    BSTNode* maxHeightDiff()
    {
        int maxDiff = 0;
        BSTNode* maxNode = new BSTNode(0);
        // return calcMaxHeight(root, maxDiff, maxNode);
        calcNew(root, &maxNode, maxDiff);
        return maxNode;
    }
    // Junski 2023. nekapiram zad
    //int countSmaller(int d) koja broji koliko ima cvorova u stablu n koji koji u svojim podstablima imaju bar jedan cvor np tako da vazi da je n - d < np < n. Resenje realizovati posebnom rekurzivnom funkcijom koju treba pozvagti iz zahtevane countSmaller sa odgovarajucim parametrima.
    // n - d < np < n   n-vrednost u cvoru, np-vrednost u potomku, d-zadata vrednost
    int countSmallerNodes(BSTNode* p, int d)
    {
        if (!p) return 0;
        //np uzima vrednost iz {n-d,n}, a posto je np manje od n ima smisla gledati samo da li je levi potomak
        int count = 0;
        if (p->left != nullptr)
        {
            if (p->left->data > (p->data - d) && p->left->data < p->data)
                count++;
        }
        //    a posto je np manje od n ima smisla gledati samo da li je levi potomak?
        //if (p->right != nullptr)
        //{
        //    if (p->right->data > (p->data - d) && p->right->data < p->data) count++;
        //}
        return count + countSmallerNodes(p->left, d) + countSmallerNodes(p->right, d);

    }
    int countSmaller(int d)
    {
        return countSmallerNodes(root, d);
    }
    // Kolokvijum II (popravni) 2023.
    // U dinamicki impl BST realizovati rekurzivnu fju koja odredjuje i vraca cvor kod koga je najveca aps 
    // vrednost razlike broja cvorova desnog i levog podstabla ciji je koren taj cvor

 //Ovo je kao Decembarski 2021.

    int findMaxAbsValue(BSTNode* p, BSTNode** maxNode, int& maxDif)
    {
        if (!p) return 0;
        int leftDif = findMaxAbsValue(p->left, maxNode, maxDif);
        int rightDif = findMaxAbsValue(p->right, maxNode, maxDif);
        int dif = abs(leftDif - rightDif);
        if (dif > maxDif)
        {
            maxDif = dif;
            *maxNode = p;
        }
        return 1 + max(leftDif, rightDif);

    }
    BSTNode* returnMaxAbsValue()
    {
        BSTNode* node = nullptr;
        int maxDif = 0;
        findMaxAbsValue(root, &node, maxDif);
        return node;
    }
    // Kolokvijum II 2023.
    /*BST dinamicki realizovati metod koji odredjuje i vraca cvor kod koga je najveca razlika
    izmedju sume parnih i neparnih cvorova u njegovim podstablima*/
    int findMaxSumDifference(BSTNode* p, BSTNode** sumDiffNode, int& sumDiff, int& oddSum, int& evenSum)
    {
        if (!p) return 0;
        //ovo dobija od ovih drugih:
        int evenSum = 0, oddSum = 0;
        int leftSubtree = findMaxSumDifference(p->left, sumDiffNode, sumDiff);
        int rightSubtree = findMaxSumDifference(p->right, sumDiffNode, sumDiff);
        int diff = abs(leftSubtree - rightSubtree);
        if (diff > sumDiff)
        {
            *sumDiffNode = p;
            sumDiff = diff;
        }
        p->data % 2 == 0 ? evenSum++ : oddSum++;
        return diff + evenSum + oddSum;
    }
    BSTNode* maxSumDifference()
    {
        BSTNode* maxNode = nullptr;
        int maxSum = 0;
        findMaxSumDifference(root, &maxNode, maxSum);
        return maxNode;
    }


    // Junski 2022.
    bool isPerfectlyBalanced(BSTNode* node, int& numNodes)
    {
        if (node == nullptr)
        {
            numNodes = 0;
            return true;
        }

        int leftNodes = 0, rightNodes = 0;
        bool leftBalanced = isPerfectlyBalanced(node->left, leftNodes);
        bool rightBalanced = isPerfectlyBalanced(node->right, rightNodes);

        numNodes = leftNodes + rightNodes + 1;

        if (!leftBalanced || !rightBalanced || abs(leftNodes - rightNodes) > 1)
            return false;

        return true;
    }
    bool isPerfect()
    {
        int numNodes = 0;
        return isPerfectlyBalanced(root, numNodes);
    }

    //Septembarski 2022.
    int countNodesInRange(BSTNode* root, int min, int max)
    {
        if (root == nullptr)
            return 0;

        if (root->data > max)
            countNodesInRange(root->left, min, max); // pretrazi levo podstablo
        else if (root->data < min)
            countNodesInRange(root->right, min, max); // pretrazi desno podstablo
        else
            return 1 + countNodesInRange(root->left, min, max) + countNodesInRange(root->right, min, max);
    }

    //Oktobarski 2022.
    //Za uredjeno dinamicki impl BST napisati rekurzivnu fju koja broji koliko u stablu ima dece ciji se info deo razlikuje
    // za 1 od njihovog roditeljskog cvora
    //int countCloseSiblings(BSTNode* root) 
    int countCloseSiblings(BSTNode* p)
    {
        if (p == nullptr)
            return 0;
        int count = 0;
        if (p->right != nullptr && abs(p->data - p->right->data) == 1)
            count++;
        if (p->left != nullptr && abs(p->data - p->left->data) == 1)        // ovo moze samo jednim if statementom
            count++;
        return count + countCloseSiblings(p->left) + countCloseSiblings(p->right);
    }
    /*int countCloseSiblings(BSTNode* root) {
        if (!root)
            return 0;

        int count = 0;
        if (root->left != nullptr)
        {
            if (abs(root->data - root->left->data) == 1)
            {
                count++;
            }
            count += countCloseSiblings(root->left);
        }
        if (root->right != nullptr)
        {
            if (abs(root->data - root->right->data) == 1)
            {
                count++;
            }
            count += countCloseSiblings(root->right);
        }
        return count;
    }*/

    //Oktobar II 2021.
    //BSTNode* getNNode() vraca cvor neuredjenog dinamickog binarnog stabla za koji vazi da ima za 2 vise cvorova u desnom nego u levom podstablu
    //  ako postoji vise, vraca bilo koji; ako ne postoji vraca null
    int getNodeTwoDiff(BSTNode* p, BSTNode** twoDiff)
    {
        if (!p)
        {
            *twoDiff = nullptr;
            return 0;
        }
        int countRight = 0;
        int countLeft = 0;
        if (p->right != nullptr)
        {
            countRight += getNodeTwoDiff(p->right, twoDiff);
        }
        if (p->left != nullptr)
        {
            countLeft += getNodeTwoDiff(p->left, twoDiff);
        }
        if (countRight - countLeft == 2)
        {
            *twoDiff = p;
        }
        return 1 + countRight + countLeft;
    }
    BSTNode* getNNode()
    {
        BSTNode* node = nullptr;
        getNodeTwoDiff(root, &node);
        return node;
    }
    int countSingleLeavesNodes(BSTNode* p) // broji koliko njih ima samo 1 list kao potomak
    {
        if (!p)
            return 0;
        int count = 0;
        count += countSingleLeavesNodes(p->left);
        count += countSingleLeavesNodes(p->right);
        if ((!p->left && p->right) || (p->left && !p->right))
            //if ((!p->left && p->right && !p->right->left && !p->right->right) || 
            //    (p->left && !p->right && !p->left->left && !p->left->right))
            count++;
        return count;
    }

    //Jun II 2021.
    /*metoda BSTNode* findNodeWithLargestRightSubtree()
    vraca cvor dinamicki implementiranog binarnog stabla trazenja sa najvecim brojem cvorova u svom desnom podstablu*/
    int nodeWithLargestRightSubtree(BSTNode* p, BSTNode** node, int& numNodes)
    {
        if (!p)
            return 0;
        int leftSubtree = 0, rightSubtree = 0;
        if (p->right)
        {
            leftSubtree = nodeWithLargestRightSubtree(p->right->left, node, numNodes);
            rightSubtree = nodeWithLargestRightSubtree(p->right->right, node, numNodes);
        }
        int sum = leftSubtree + rightSubtree;
        if (numNodes < sum)
        {
            *node = p;
            numNodes = sum;
        }
        return 1 + sum;
    }
    BSTNode* findNodeWithLargestRightSubtree()
    {
        BSTNode* node = nullptr;
        int suma = 0;
        nodeWithLargestRightSubtree(root, &node, suma);
        return node;

    }

   ///* int findSibling(int target) 
   // {
   //     if (root == nullptr) 
   //         return -1;

   //     queue<BSTNode*> queueCurr;
   //     queue<BSTNode*> queueNext;
   //     queueCurr.push(root);

   //     while (!queueCurr.empty()) {
   //         int levelSize = queueCurr.size();
   //         bool foundTarget = false;
   //         for (int i = 0; i <= levelSize; i++) 
   //         {
   //             BSTNode* currentNode = queueCurr.front();
   //             queueCurr.pop();
   //             
   //             if ((currentNode->left && currentNode->left->data == target) || (currentNode->right && currentNode->right->data == target))
   //                 foundTarget = true;

   //             if (currentNode->left) 
   //                 queueNext.push(currentNode->left);
   //             if (currentNode->right) 
   //                 queueNext.push(currentNode->right);
   //         }
   //         if(!foundTarget) 
   //             swap(queueCurr, queueNext);
   //         else
   //         {
   //             while (!queueNext.empty())
   //             {
   //                 if (queueNext.front()->data != target)
   //                     return queueNext.front()->data;
   //                 else queueNext.pop();
   //             }
   //         }
   //     }
   //     return -1;
   // }*/

};


int main(int argc, char* argv[])
{

    BSTTree* tree = new BSTTree();

    //int B[] = { 7,3,8,1,5,9,2,6,4 };
    //for (int i = 0; i < 9; i++)
    //    tree->IterativeInsert(B[i]);

    int A[] = { 25,20,36,10,22,30,40,5,12,28,38,48,1,8,15,45,50 };
    //int A[] = { 5,3,7, 2, 4, 6, 8 };
    //int A[] = { 6,9,4,1,8,2 };
    int N = sizeof(A) / sizeof(A[0]);
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
        tree->IterativeInsert(A[i]);

    //tree->printBT(tree->root);

    //BSTNode* found = tree->IterativeSearch(5);
    //if(found)
    //    cout << "Data " << found->data << " is found" << endl;
    // 
    //bool found = tree->Search(tree->root, 4);
    //if (found) cout << "Found!" << endl; else cout << "Not found" << endl;

    //BSTNode* cvor = tree->findMin(tree->root); //findMax
    //cout << cvor->data << endl;

    cout << "POSTORDER:" << endl;
    tree->Postorder(tree->root);
    cout << endl;
    tree->iterativePostorder(tree->root);
    cout << endl;

    //tree->levelOrder(tree->root);
    // 
    //tree->root->right->right->data = 2;
    //tree->root->left->right->left->data = 7;

    tree->printBT(tree->root);
    cout << "______________________________________" << endl;
    tree->deleteByCopyingRecursive(tree->root, 2);
    tree->printBT(tree->root);
    cout << "______________________________________" << endl;
    if (tree->isIt(tree->root)) cout << "It is BST" << endl;
    else cout << "It isn't BST" << endl;

    cout << "Visina stabla je " << tree->calcHeight(tree->root) << endl;
    cout << "Broj cvorova je " << tree->countNodes(tree->root) << endl;

    BSTNode* max = tree->maxHeightDiff();
    cout << "cvor sa najvecom razlikom visina: " << max->data << endl;
    if (tree->isPerfect())cout << "Perfektno je balansirano" << endl; else cout << "nie perfektno balansirano" << endl;

    cout << tree->countNodesInRange(tree->root, 4, 7) << endl;
    //int maxsum = 0;
    //BSTNode* maxnode = nullptr;
    //BSTNode* maxSum = tree->maxSumNodes(tree->root, maxsum, &maxnode);
    //cout << "cvor sa najvecom sumom direktnih potomaka: " << maxSum->data << endl;

    cout << tree->countCloseSiblings(tree->root) << endl;
    BSTNode* min = tree->findMin(tree->root);
    cout << "Cvor " << min->data << " je na dubini " << tree->getDepth(min) << endl;
    cout << "koliko ima " << tree->countSmaller(2) << endl;

    //BSTNode* abs = tree->returnMaxAbsValue();
    //cout << "cvor sa najvecom aps razlikom cvorova: " << abs->data << endl;

    //BSTNode* two = tree->getNNode();
    //cout << "cvor sa 2 razlike: " << two->data << endl;
    //cout << "Broj cvorova sa samo 1 listom: " << tree->countSingleLeavesNodes(tree->root) << endl;

    BSTNode* right = tree->findNodeWithLargestRightSubtree();
    cout << "cvor sa najvecim brojem cvorova u desnom podstablu: " << right->data << endl;

    //cout << tree->findSibling(50) << endl;

    return 0;
}
