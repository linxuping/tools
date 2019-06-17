package main

import (
    "fmt"
)

type Node struct {
    m int
    left  *Node
    right *Node
}


func visit_node(node *Node) {
    if (node == nil) {
        return
    }
    visit_node(node.left)
    fmt.Println(node.m)
    visit_node(node.right)
}

func get_node_depth(node *Node) int {
    if (node == nil) {
        return 0
    }
    d1 := get_node_depth(node.left)
    d2 := get_node_depth(node.right)
    if (d1 > d2) {
        return d1+1 
    }
    return d2+1 
}



func main() {
    root := Node{m:2}

    root.left = &Node{m:1}
    root.right = new(Node)
    root.right.m = 3 

    root.left.left = &Node{m:11}
    root.left.right = &Node{m:12}

    fmt.Printf("%+V\n", root)

    visit_node(&root)
    fmt.Println("Tree depth: ")
    fmt.Println( get_node_depth(&root) )
}


