using System.Threading.Tasks;
using Grpc.Net.Client;
using PricingClient;

// Le numéro de port doit correspondre au port du serveur gRPC.
using var channel = GrpcChannel.ForAddress("http://localhost:50051");
