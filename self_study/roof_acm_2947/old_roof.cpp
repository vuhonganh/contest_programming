#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define FOR(i, a, b) for(int i = (a), i < (b); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

#define INF 1000000000 
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool debug = false;
int checkRead;
//done shortcut
////////////////

//the low value of interval is used as key to maintain order in BST
struct Interval
{
  int low; int high; int ylow; int yhigh; int id; int litre;
};

struct ITNode
{
  Interval *i;
  int max;//maximum high value in subtree rooted with this node
  int min;//minimum low value in subtree rooted with this node
  ITNode *left, *right;  
};

ITNode * newNode(Interval i)
{
  ITNode *temp = new ITNode;
  temp->i = new Interval(i);
  temp->max = i.high;
  temp->min = i.low;
  temp->left = temp->right = NULL; 

  return temp;
}

ITNode *insert(ITNode *root, Interval i)
{
  if(root == NULL)
    return newNode(i);

  //get low value of interval at root
  int l = root->i->low;

  //if root's low value is bigger then new interval goes to left subtree
  if(i.low <= l)
    root->left = insert(root->left, i);
  else
    root->right = insert(root->right, i);

  //update max if needed
  if(root->max < i.high)
    root->max = i.high;
  if(root-> min > i.low)
    root->min = i.low;
  
  return root;
}

void delTree(ITNode *root)
{
  if(root != NULL)
    {
      delTree(root->left);
      delTree(root->right);
      delete root;
    }
}

ITNode* clearTree(ITNode *root)
{
  delTree(root);
  return NULL;
}

bool isOverlap(Interval i1, Interval i2)
{
  bool notOverlap = ((i1.high < i2.low) || (i2.high < i1.low));
  return !notOverlap;
}

bool isContained(Interval &i, int nb)
{
  return ( (i.low <= nb) && (nb <= i.high));
  
}

void inorder(ITNode *root)
{
  if(root == NULL) return;

  inorder(root->left);
  printf("[%d, %d], max = %d\n", root->i->low, root->i->high, root->max);
  inorder(root->right);
}

void containsSearch(ITNode *root, const int &nb, queue<Interval> &container)
{
  //base case
  if(root == NULL) return;
  if(root->max < nb || root->min > nb) return; 

  if(isContained( * (root->i), nb)) container.push( *(root->i));
  
  //search right tree if it could contain nb
  if(root->right != NULL && root->right->max >= nb)
    containsSearch(root->right, nb, container);
  //search left tree
  if(root->left != NULL && root->left->min <= nb)
    containsSearch(root->left, nb, container);
}

Interval *overlapSearch(ITNode *root, Interval i)
{
  if(root == NULL) return NULL;

  if(isOverlap( * (root->i), i))
    return root->i;
  
  if(root->left != NULL && root->left->max >= i.low)
    return overlapSearch(root->left, i);
  
  return overlapSearch(root->right, i);
}



void printInterval(const Interval &i)
{
  printf("[(%d, %d), (%d, %d)] at index %d, contains %d litres\n", i.low, i.ylow, i.high, i.yhigh, i.id, i.litre);  
}

void test()
{
  // init
  Interval ints[] = {{15, 20, 1, 1, 0, 0}, {10, 30, 1, 1, 1, 0}, {17, 19, 1, 1, 2, 0},
		     {5, 20, 1, 1, 3, 0}, {12, 15, 1, 1, 4, 0}, {30, 40, 1, 1, 5, 0}};
  int n = sizeof(ints)/sizeof(ints[0]);
  ITNode *root = NULL;
  for (int i = 0; i < n; i++)
    root = insert(root, ints[i]);
  
  cout << "Inorder traversal (left mid right) of constructed Interval Tree is\n";
  inorder(root);
  
  cout << "clear Tree\n";
  root = clearTree(root); 

  if(root == NULL) cout << "tree null now\n";
  cout << "print tree encore\n";
  inorder(root);
  /*
  //search for interval contain
  int nb = 17;
  printf("search interval contain %d\n", nb);
  queue<Interval> container;
  
  containsSearch(root, nb, container);
  while(!container.empty())
    {
      Interval ic = container.front(); container.pop();
      printInterval(ic);
    }
  */ 
}

int n;
int in_xlow, in_ylow, in_xhigh, in_yhigh;
ITNode *root = NULL;
priority_queue <int, vector<int>, greater<int> > pq;
//set <int, greater<int> > xEndPoints;
set <int> xEndPoints;

void readIn()
{
  //init and clear old var
  root = clearTree(root);
  xEndPoints.clear();

  //read input
  checkRead = scanf("%d", &n); assert(checkRead == 1);
  REP(i, n)
    {
       checkRead = scanf("%d %d %d %d", &in_xlow, &in_ylow, &in_xhigh, &in_yhigh); assert(checkRead == 4);
       Interval cur = {in_xlow, in_xhigh, in_ylow, in_yhigh, i, 0};
       root = insert(root, cur);
       xEndPoints.insert(in_xlow);
       xEndPoints.insert(in_xhigh);
    }
}

//yLow of above will "drop" into interval below
int cut_yLow(Interval &above, queue<Interval *> ptrToInterval)
{
  int index;
  double maxHeight = -1;
  while(!ptrToInterval.empty()
    {
      Interval below = * (ptrToInterval.front()); ptrToInterval.pop();
            
      //height of intersection 
      double height = 1.0 * (below.yhigh - below.ylow) / (below.high - below.low) * (above.low - below.ylow);
      if(maxHeight < height)
	{
	  maxHeight = height;
	  index = below.id;
	}
    }
  
}


void testSet()
{
  xEndPoints.insert(5);
  xEndPoints.insert(3);
  xEndPoints.insert(9);
  xEndPoints.insert(7);
  xEndPoints.insert(5);

  FOREACH(i, xEndPoints)
    {
      cout << *i << endl;
    }
}


int main()
{
  /*
  int nbCases;
  checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
  while(nbCases--)
    {
      readIn();
      compute();
    }
  */

  //testSet();
  test();
  return 0;
}
