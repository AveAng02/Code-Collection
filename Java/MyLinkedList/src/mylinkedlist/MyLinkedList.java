/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package mylinkedlist;

/**
 *
 * @author AYAN ACHARYA
 * @param <E>
 */
public class MyLinkedList<E> extends MyAbstractList<E> {
    
    private Node<E> head, tail; 
    private int size;
    
    public MyLinkedList(){
        
    }
    
    public E getFirst(){
        if(size == 0){
            return null;
        }
        else{
            return head.element;
        }
    }
    
    public E getLast(){
        if(size == 0){
            return null;
        }
        else{
            return tail.element;
        }
    }
    
    public void addFirst(E e){
        Node<E> newNode = new Node<>(e);
        newNode.next = head;
        head = newNode;
        size++;
        
        if(tail == null){
            tail = head;
        }
    }
    
    public void addLast(E e){
        Node<E> newNode = new Node<>(e);
        
        if(tail == null){
            head = tail = newNode;
        }
        else{
            tail.next = newNode;
            tail = tail.next;
        }
        
        size++;
    }
    
    public void add(int index, E e){
        if(index == 0){
            addFirst(e);
        }
        else if(index >= size){
            addLast(e);
        }
        else{
            Node<E> current = head;
            for(int i = 1; i < index; i++){
                current = current.next;
            }
            Node<E> temp = current.next;
            current.next = new Node<E>(e);
            (current.next).next = temp;
            size++;
        }
    }
    
    public E removeFirst(){
        if(size == 0){
            return null;
        }
        else{
            Node<E> temp = head;
            head = head.next;
            size--;
            if(head == null){
                tail = null;
            }
            return temp.element;
        }
    }
    
    public E removeLast(){
        if(size == 0){
            return null;
        }
        else if (size == 1){
            Node<E> temp = head;
            head = tail = null;
            size = 0;
            return temp.element;
        }
        else{
            Node<E> current = head;
            
            for(int i = 0; i < size - 2; i++){
                current = current.next;
            }
            
            Node<E> temp = tail;
            tail = current;
            tail.next = null;
            size--;
            return temp.element;
        }
    }
    
    public E remove(int index){
        if(index < 0 || index >= size){
            return null;
        }
        else if(index == 0){
            removeFirst();
        }
        else if(index == size - 1){
            return removeLast();
        }
        else{
            Node<E> previous = head;
            
            for(int i = 1; i < index; i++){
                previous = previous.next;
            }
            
            Node<E> current = previous.next;
            previous.next = current.next;
            size--;
            return current.element;
        }
        return null;
    }
    
    @Override
    public String toString(){
        StringBuilder result = new StringBuilder("[");
        
        Node<E> current = head;
        
        for(int i = 0; i < size; i++){
            result.append(current.element);
            current = current.next;
            if(current != null){
                result.append(", "); // Seperate two elements 
            }
            else{
                result.append("]");
            }
        }
        return result.toString();
    }
    
    public void clear(){
        size = 0;
        head = tail = null;
    }
    
    public boolean contains(E e){
        Node<E> current = head;
        
        for(int i = 0; i < size; i++){
            if(current.element.equals(e)){
                return true;
            }
        }
        
        return false;
    }
    
    public E get(int index){
        Node<E> current = head;
        
        if(index < size - 1 && index > 0){
            for(int i = 0; i < index - 1; i++){
                current = current.next;
            }
            return current.element;
        }
        else{
            return null;
        }
    }
    
    public int indexOf(E e){
        Node<E> current = head;
        
        for(int i = )
    }
    
    
}

class Node<E> {
    E element;
    Node<E>  next;
    
    public Node(E element){
        this.element = element;
    }
}