package t1;

import java.util.ArrayList;
import java.util.Comparator;

public class myPriorityQueue<T>{

	private ArrayList<T> list;
	int size;
	
	public myPriorityQueue(){
		list = new ArrayList<T>();
		size=0;
	}
	
	public T extractMax(){
		T max = list.get(0);
		list.remove(0);
		size--;
		return max;
	}
	
	public T max(){
		return list.get(0);
	}
	
	public void insert(T x){
		list.add(x);
		heapUp(list.size()-1);
		size++;
	}
	
	public void increaseKey(int i, T x){
		Comparable<T> key = (Comparable) x;
		if(key.compareTo(list.get(i))<0){
			System.out.println("new key is smaller than current key");
			return;
		}
		heapUp(i);
	}
	
	public void heapDown(int i){
		if(2*i<size){
			
		}
	}
	
	public void heapUp(int i){
		
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
