using System.Threading.Tasks;
using Grpc.Net.Client;
using PricingClient;

// The port number must match the port of the gRPC server.
/*using var channel = GrpcChannel.ForAddress("https://localhost:7236");
var client = new GrpcPricer.PricingServiceClient(channel);
var replyHello = await client.SayHelloAsync(
                  new HelloRequest { Name = "GreeterClient" });
Console.WriteLine("Greeting: " + replyHello.Message);

var replyGoodbye = await client.SayGoodbyeAsync(
                  new GoodbyeRequest { Name = "GreeterClient" });
Console.WriteLine("Goodbye: " + replyGoodbye.Message);


var assetPriceReply = await client.GetAssetPriceAsync(new AssetRequest { AssetSymbol = "AAPL" });
Console.WriteLine($"Price of AAPL: {assetPriceReply.Price}");

Console.WriteLine("Press any key to exit...");
Console.ReadKey();*/



// Le numéro de port doit correspondre au port du serveur gRPC.
using var channel = GrpcChannel.ForAddress("http://localhost:50051");
var client = new GrpcPricer.GrpcPricerClient(channel);
var heartbeatResponse = await client.HeartbeatAsync(new Empty());
Console.WriteLine($"Domestic Interest Rate: {heartbeatResponse.DomesticInterestRate}");
Console.WriteLine($"Relative Finite Difference Step: {heartbeatResponse.RelativeFiniteDifferenceStep}");
Console.WriteLine($"Sample Number: {heartbeatResponse.SampleNb}");
Console.WriteLine("Press any key to exit...");
Console.ReadKey();