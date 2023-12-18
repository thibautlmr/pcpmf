using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;
using Grpc.Core;
using PricingClient;
using Grpc.Net.Client;
public static class GrpcClientUtil
{
    public static async Task<ReqInfo> GetHeartbeatInfoAsync(string serverAddress)
    {
        var httpHandler = new HttpClientHandler();
        httpHandler.ServerCertificateCustomValidationCallback = HttpClientHandler.DangerousAcceptAnyServerCertificateValidator;

        using var channel = GrpcChannel.ForAddress(serverAddress, new GrpcChannelOptions { HttpHandler = httpHandler });
        var client = new GrpcPricer.GrpcPricerClient(channel);

        try
        {
            var heartbeatResponse = await client.HeartbeatAsync(new Empty());
            return heartbeatResponse;
        }
        catch (RpcException e)
        {
            Console.WriteLine($"Error: {e.Status}");
            return null;
        }
    }
}