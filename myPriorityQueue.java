package datastructures;

import java.util.ArrayList;
import java.util.Comparator;

public class myPriorityQueue{

	private int list[];
	int size;
	int pos;
	
	public myPriorityQueue(int n){
		list = new int[n];
		size=n;
		pos=0;
	}
	
	public int extractMax(){
		if(size == 0){
			System.out.println("queue is empty");
			return Integer.MIN_VALUE;
		}
		int max = list[1];
		for(int i=2; i<size; i++)
			list[i-1] = list[i];
		size--;
		return max;
	}
	
	public int max(){
		if(size == 0){
			System.out.println("queue is empty");
			return Integer.MIN_VALUE;
		}
		int maxVal = list[1];
		list[1] = list[size];
		size--;
		heapDown(1);
		return maxVal;
	}
	
	public void insert(int x){
		list[++pos] = x;
		heapUp(pos);
	}
	
	public void increaseKey(int i, int x){
		if(x<list[i]){
			System.out.println("new key is smaller than current key");
			return;
		}
		heapUp(i);
	}
	
	public void heapDown(int i){
		int j, k, x;
		k = i;
		j=2*k;
		x = list[k];
		while(j<size){
			if(list[j]<list[j+1]) j++;
			if(x<list[j]){
				list[k] = list[j];
				k = j;
				j<<=1;
			}
			else
				break;
		}
		if(j==size && x<list[j]){
			list[k] = list[j];
			k = j;
		}
		list[k] = x;
	}
	
	public void heapUp(int i){
		int j, k, x;
		k = i;
		x = list[k];
		while(k>1 && x>list[k/2]){
			list[k] = list[k/2];
			k>>=1;
		}
		list[k] = x;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		myPriorityQueue queue = new myPriorityQueue(10);
		queue.insert(4);
		queue.insert(7);
		queue.insert(90);
		queue.insert(45);
		queue.insert(1);
		for(int i=0; i<5; i++)
			System.out.println(queue.extractMax());
	}

}