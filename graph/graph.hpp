#pragma once

//基本概念：
//定义：图是由顶点的有穷非空集合和顶点之间的边的集合组成，通常表示为：G(V,E)，其中，G表示一个图，V是图G中顶点的集合，E是图G中边的集合。
//无向边：若顶点Vi 到Vj 的边没有方向，则称这条边为无向边，用无序偶对（Vi ，Vj）(无序对)来表示。
//无向图：如果图中任意两个顶点之间的边都是无向边，则称该图为无向图。
//无向完全图：在无向图中，如果任意两个顶点之间都存在边，则称该图为无向完全图。含有n个顶点的无向完全图有n(n-1)/2条边。(没新增一个节点，都要让当前节点和所有其他节点建立链接，所以总的边树是0+1+2＋3...+n-1)

//有向边：若从顶点Vi 到Vj的边有方向，则称这条边为有向边，也称为弧。用有序偶对<Vi ，Vj>(有序对)来表示。Vi称为弧尾，Vj称为弧头。
//有向图：如果图中任意顶点之间的边都是有向边，则称该图为有向图。
//有向完全图：在有向图中，如果任意两个顶点之间都存在方向互为相反的两条弧，则称该图为有向完全图。含有n个顶点的有向完全图有n(n-1)条边(道理同无向完全图)。

//因此，对于有n个顶点和e条边数的图，无向图0<=e<=n(n-1)/2，有向图0<=e<=n(n-1)。
//路径长度：路径的长度是路径上的边或弧的数目.
//图中顶点之间有邻接点、依附的概念。无向图顶点的边数叫做度，有向图顶点分为入度和出度。
//图上的边或弧带权则称为网。


//稀疏&稠密：有很少条边或弧的图称为稀疏图，反之称为稠密图。
//简单图：

//图和树：树是一种特殊的图。树将节点有规律的组合到了一块，所以从某种意义上说树是一种特殊的图结构
//生成树：从图中任意一顶点出发遍历图，所经历的边的集合可看做是一个图的生成树，按照深度和广度的不同会得到不同的生成树，得到的生成树也是该图的一个子图。
//最小生成树：由于生成树不唯一，从不同的顶点出发可以得到不同的生成树。对连通网来说，边是带权值的，构造出具有最小权值的生成树就是最小生成树。构造最小生成树有多重算法，下面介绍两种最常用的。
//普利姆算法: 以一个顶点集合U={μ}作初态，不断寻找与U中顶点相邻且代价最小的边的另一个顶点，扩充U集合直至U中顶点包括所有的顶点为止。
//克鲁斯卡尔算法:

#include <iostream>

template<class V, class W> // V->节点集合, W->边权值
class graph_matrix{
	public:
		graph_matrix()
		{}

		//_vertexs定点的集合，_size定点的大小
		graph_matrix(const V *_vertexs, int _size)
			:matrix_size(_size)
		{
			vertexs = new V[_size]; //申请空间，向量，保存节点信息
			matrix  = new W*[_size]; //开辟矩阵
			int i = 0;
			for( ; i < _size; i++ ){
				//初始化矩阵
				matrix[i] = new W[_size];
				memset(matrix[i], 0, sizeof(W)*_size);

				//初始化边集
				vertexs[i] = _vertexs[i];
			}
		}

		//获取边对应索引
		int get_vertexs_index( const V &_vtx )
		{
			int i = 0;
			for( ; i < matrix_size; ++i ){
				if( _vtx == vertexs[i] ){
					return i;
				}
			}

			return -1;
		}

		//添加边到临接矩阵
		//指定源节点->目标节点
		void add_edge(const V &_src, const V &_dst, const W &_weight)
		{
			int src_index = get_vertexs_index( _src );
			int dst_index = get_vertexs_index( _dst );

			if( src_index != -1 && dst_index != -1 ){
				matrix[src_index][dst_index] = _weight;
			}
		}

		void display()
		{
		}

		~graph_matrix()
		{}
	private:
		V* vertexs; //顶点集合
		W** matrix; //临接矩阵
		int matrix_size; //顶点个数
};







