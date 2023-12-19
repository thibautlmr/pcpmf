using MarketData;
using ParameterInfo;
using ParameterInfo.RebalancingOracleDescriptions;
using ParameterInfo.JsonUtils;

namespace FinancialApp
{
    public class DataUtilities
    {
        public List<DataFeed> MarketData { get; set; }
        public TestParameters TestParameters { get; set; }
        public Input Input { get; set; }
        public DataUtilities(Input input)
        {
            Input = input;
            string json = File.ReadAllText(input.TestParamsPath);
            TestParameters = JsonIO.FromJson(json);
            MarketData = MarketDataReader.ReadDataFeeds(input.MarketDataPath);
        }

        public List<DateTime> GetDateTimes(List<DataFeed> shares)
        {
            List<DateTime> dateTimes = new();
            foreach (DateTime date in shares.Select(share => share.Date).Where(date => !dateTimes.Contains(date)))
            {
                dateTimes.Add(date);
            }
            return dateTimes;
        }

        public DataFeed GetDataFeedForOneDate(DateTime dateTime)
        {
            foreach (DataFeed share in MarketData)
            {
                if (share.Date == dateTime)
                {
                    return share;
                }
            }
            return null;
        }

        public List<string> GetIds()
        {
            return MarketData[0].SpotList.Keys.ToList();
        }

        public double[] GetSpots(DateTime date)
        {
            List<string> ids = GetIds();
            int nbAssets = MarketData[0].SpotList.Count;
            double[] spots = new double[nbAssets];
            DataFeed marketDataCurrDate = GetDataFeedForOneDate(date);
            for (int i = 0; i < nbAssets; i++)
            {
                spots[i] = marketDataCurrDate.SpotList[ids[i]];
            }
            return spots;
        }
    }
}