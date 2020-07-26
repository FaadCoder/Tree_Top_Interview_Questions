#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const ll mod=1e9+7;
#define take_input freopen("input.txt","r",stdin),freopen("output.txt","w",stdout);
#define fast ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);

class tree{
public:
	ll val;
	tree *left,*right;

	tree(ll value)
	{
		this->val=value;
		this->left=this->right=NULL;
	}
	tree *insert(ll value,tree *root)
	{
		if(root==NULL)
			return new tree(value);
		if(value<root->val)
			root->left=insert(value,root->left);
		else
			root->right=insert(value,root->right);
		return root;
	}
	void inorder(tree *root)
	{
		if(root==NULL)
			return;
		inorder(root->left);
		cout<<root->val<<" ";
		inorder(root->right);
	}
	void preorder(tree *root)
	{
		if(root==NULL)
			return;
		cout<<root->val<<" ";
		preorder(root->left);
		preorder(root->right);
	}
	void postorder(tree *root)
	{
		if(root==NULL)
			return;
		postorder(root->left);
		postorder(root->right);
		cout<<root->val<<" ";
	}
	void level_order_traversal(tree *root)
	{
		queue<tree *> q;
		q.push(root);
		while(!q.empty())
		{
			auto temp=q.front();
			q.pop();
			cout<<temp->val<<" ";
			if(temp->left!=NULL)
				q.push(temp->left);
			if(temp->right!=NULL)
				q.push(temp->right);
		}
	}
	void left_view(tree *root)
	{
		queue<tree *> q;
		q.push(root);
		while(!q.empty())
		{
			int sz=q.size();
			for(int i=1;i<=sz;i++)
			{
				auto temp=q.front();
				q.pop();
				if(i==1)
					cout<<temp->val<<" ";
				if(temp->left)
					q.push(temp->left);
				if(temp->right)
					q.push(temp->right);
			}
		}
	}
	void right_view(tree *root)
	{
		queue<tree *> q;
		q.push(root);
		while(!q.empty())
		{
			int sz=q.size();
			for(int i=1;i<=sz;i++)
			{
				auto temp=q.front();
				q.pop();
				if(i==sz)
					cout<<temp->val<<" ";
				if(temp->left)
					q.push(temp->left);
				if(temp->right)
					q.push(temp->right);
			}
		}
	}

	ll get_tree_height(tree *root)
	{
		if(root==NULL)
			return 0;
		ll left=get_tree_height(root->left);
		ll right=get_tree_height(root->right);
		return 1+max(left,right);
	}
	tree *array_to_bst(ll *a,ll st,ll end)
	{
		if(st>end)
			return NULL;
		ll middle=(st+end)>>1;
		tree *root=new tree(a[middle]);
		root->left=array_to_bst(a,st,middle-1);
		root->right=array_to_bst(a,middle+1,end);
		return root;
	}
	tree *create_tree_preorder_inorder(int &pre_idx,ll st,ll end,ll *pre,auto &mp)
	{
		if(st>end)
			return NULL;
		tree *root=new tree(pre[pre_idx]);
		int idx=mp[pre[pre_idx]];
		pre_idx++;
		root->left=create_tree_preorder_inorder(pre_idx,st,idx-1,pre,mp);
		root->right=create_tree_preorder_inorder(pre_idx,idx+1,end,pre,mp);
		return root;
	}
	bool is_identical_trees(tree *root1,tree *root2)
	{
		// BOTH trees are empty
		if(root1==NULL and root2==NULL)
			return true;
		if(root1==NULL or root2==NULL)
			return false;
		if(root1->val!=root2->val)
			return false;
		return is_identical_trees(root1->left,root2->left) and is_identical_trees(root1->right,root2->right);
	}
	bool is_mirror_tree(tree *root1,tree *root2)
	{
		// BOTH trees are empty
		if(root1==NULL and root2==NULL)
			return true;
		if(root1==NULL or root2==NULL)
			return false;
		if(root1->val!=root2->val)
			return false;
		return is_mirror_tree(root1->left,root2->right) and is_mirror_tree(root1->right,root2->left);
	}
	void serialize_tree(tree *root,FILE *fp)
	{
		if(root==NULL)
		{
			fprintf(fp,"%d ",-1);
			return;
		}
		fprintf(fp,"%lld ",root->val);
		serialize_tree(root->left,fp);
		serialize_tree(root->right,fp);
	}
	tree *deserialize(FILE *fp)
	{
		ll value;
		if(!fscanf(fp,"%lld",&value) or value==-1)
			return NULL;
		tree *root=new tree(value);
		root->left=deserialize(fp);
		root->right=deserialize(fp);
		return root;
	}
	void print_top_view(tree *root)
	{
		map<int,int> mp;
		queue<pair<tree *,int>> q;
		q.push({root,0});
		while(!q.empty())
		{
			auto temp=q.front();
			q.pop();
			int hd=temp.second;
			auto node=temp.first;
			if(mp.count(hd)==0)
			{
				mp[hd]=node->val;
			}
			if(node->left)
			{
				q.push({node->left,hd-1});
			}
			if(node->right)
			{
				q.push({node->right,hd+1});
			}
		}
		for(auto i:mp)
			cout<<i.second<<" ";
	}
	void print_bottom_view(tree *root)
	{
		map<int,int> mp;
		queue<pair<tree *,int>> q;
		q.push({root,0});
		while(!q.empty())
		{
			auto temp=q.front();
			q.pop();
			int hd=temp.second;
			auto node=temp.first;
			mp[hd]=node->val;
			if(node->left)
			{
				q.push({node->left,hd-1});
			}
			if(node->right)
			{
				q.push({node->right,hd+1});
			}
		}
		for(auto i:mp)
			cout<<i.second<<" ";
	}
	void binary_tree_to_dll(tree *root,auto &head,auto &prev)
	{
		if(!root)
			return;
		binary_tree_to_dll(root->left,head,prev);
		if(prev==NULL)
		{
			head=root;
		}
		else
		{
			root->left=prev;
			prev->right=root;
		}
		prev=root;
		binary_tree_to_dll(root->right,head,prev);
	}
};

int main()
{
	fast;
	// take_input;
	tree *root1=NULL;
	root1=root1->insert(7,root1);
	root1=root1->insert(2,root1);
	root1=root1->insert(8,root1);
	root1=root1->insert(1,root1);
	root1=root1->insert(5,root1);
	
	tree *head=NULL,*prev=NULL;
	root1->binary_tree_to_dll(root1,head,prev);
	tree *temp=head;

	while(temp!=NULL)
	{
		cout<<temp->val<<" ";
		temp=temp->right;
	}
}
