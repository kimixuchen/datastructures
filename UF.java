/**
 * Union-find implementation
 * xuchen
 */
package t1;

import java.util.Scanner;

public class UF {

	private int[] id; // access to component id (site indexed)
	private int[] rank; //rank of a root node
	private int count; // number of components

	public UF(int N)
	{ // Initialize component id array.
		count = N;
		id = new int[N+5];
		rank = new int[N+5];
		for (int i = 0; i < N; i++){
			id[i] = i;
			rank[i] = 0;
		}
		
	}
	
	public int count()
	{ return count; }
	
	public boolean connected(int p, int q)
	{ return find(p) == find(q); }
	
	public int find(int p)
	{
		while(id[p] != p)
		{
			id[p] = id[id[p]];
			p = id[p];
		}
		return id[p];
	}
	
	public void union(int p, int q)
	{
		int i = find(p);
		int j = find(q);
		if (i == j) return;
		// Make smaller root point to larger one.
		if (rank[i] < rank[j]) { id[i] = j;}
		else { id[j] = i; rank[i]++; }
		count--;
	}
	
	public static void main(String[] args)
	{ 	// Solve dynamic connectivity problem on StdIn.
		Scanner scanner=new Scanner(System.in);
		int N = scanner.nextInt(); // Read number of sites.
		int M = scanner.nextInt();
		UF uf = new UF(N); // Initialize N components.
		while (M-- > 0)
		{
			int p = scanner.nextInt();
			int q = scanner.nextInt(); // Read pair to connect.
			if (uf.connected(p, q)) continue; // Ignore if connected.
			uf.union(p, q); // Combine components
			System.out.println(p + " " + q); // and print connection.
		}
		System.out.println(uf.count() + " components");
	}

}
