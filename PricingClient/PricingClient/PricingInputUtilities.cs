using Google.Protobuf;
using GrpcPricing.Protos;

namespace PricingClient
{
    internal class PricingInputUtilities
    {


        public PricingInput CreatePricingInput(bool isMonitoringDate, double time, List<List<double>> past)
        {
            List<PastLines> pastLines = new();
            PastLines spotLine = new();
            for (int i = 0; i < past.Count; i++)
            {
                for (int j = 0; j < past[i].Count; j++)
                {
                    spotLine.Value.Add(past[i][j]);
                }
                pastLines.Add(spotLine);
                spotLine.Value.Clear();
            }

            return new PricingInput() 
            { 
                Time = time,
                MonitoringDateReached = isMonitoringDate,
                Past = { pastLines }
            };
        }
    }
}
