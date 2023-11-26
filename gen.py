import random

def generate_graph(num_vertices):
    vertices = [f"v{i}" for i in range(1, num_vertices + 1)]
    
    with open("generated_graph.txt", "w") as file:
        for src in vertices:
            # Number of outgoing edges for each vertex (random value between 1 and 10)
            num_outgoing_edges = random.randint(1, 10)
            
            # Generate outgoing edges
            for _ in range(num_outgoing_edges):
                # Choose a random destination vertex (different from the source)
                dst = random.choice(vertices)
                while dst == src:
                    dst = random.choice(vertices)
                
                # Generate a random weight between 1 and 20
                weight = random.randint(1, 20)
                
                # Write the edge to the file
                file.write(f"{src} {dst} {weight}\n")

if __name__ == "__main__":
    num_vertices = 510
    generate_graph(num_vertices)
